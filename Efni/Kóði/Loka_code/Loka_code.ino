// Libraries
#include "NewPing.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "tdelay.h"
#include <Servo.h>

// DC mótor
const int HRADI = 5;  // Verður að vera PWM pinni
const int STEFNA_A = 2;
const int STEFNA_B = 4;
void afram(int hradi);
TDelay DC_Motorbid(2000);  //Bíður í eina sek
void bakka(int hradi);
void stoppa();

// MP3 hljóð
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(12, 13);  // RX, TX
void playSound();                         // útfært neðar
TDelay spilun(4500);                      // Tími fyrir hljóðskrá að spila í millis, 5 sekúndur hér.

// Servo
Servo motor;
int motor_pinni = 3;                // pinninn sem ég nota til að stjórna mótornum
int motor_stefnur[] = { 20, 140 };  // geymir stefnurnar sem mótorinn á að fara í og í hvaða röð
int motor_stefnu_fjoldi = 2;        // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0;       // breytan heldur utan um í hvaða stefnu mótorinn á að benda
void munnur();                      // fall útfært neðar
TDelay motor_bid(500);              // bíða í hálfa sekúndu á milli hreyfinga

void setup() {
  // Hljóð
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while (true)
      ;
  }
  myDFPlayer.volume(10);  // Set volume value. From 0 to 30

  // Servo
  motor.attach(motor_pinni);  // segi servo tilvikinu hvaða pinna á að nota
  motor.write(0);             // mótorinn að byrja í 0°
}

void loop() {
  afram(150);
  playSound();
  munnur();
}

// spilar hljóðskrá á x fresti
void playSound() {
  if (spilun.timiLidinn() == true) {
    myDFPlayer.play(1);  // Play mp3
  }
}

// DC mótor
void afram(int hradi) {
  if (DC_Motorbid.timiLidinn())
    digitalWrite(STEFNA_A, HIGH);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, hradi);
}

void stoppa() {
  digitalWrite(STEFNA_A, LOW);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, 0);
}

// sweep
void munnur(){
  if(motor_bid.timiLidinn()) {
    // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
    // aldrei hærri en fjöldi stefnanna sem eru í listanum
    motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
    // veljum svo rétta stefnu úr listanum
    motor.write(motor_stefnur[motor_stefnu_teljari]);
  }
}
