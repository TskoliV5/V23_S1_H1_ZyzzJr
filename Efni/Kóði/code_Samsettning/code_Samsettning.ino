// Libraries
#include "NewPing.h"
#include <tdelay.h>
#include <Servo.h>

// Objects
#define TRIGGER_PIN 9
#define ECHO_PIN 10


// Hversu nálagt þarf að vera til að
// kveikja á kóðanum í cm
int distance = 20;

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400



void setup() {
    Serial.begin(9600);
}

void loop() {
  if (sonar.ping_cm() < distance) {
    

    // Keyrir í staðinn ef enginn er nálagt
    } else {
    
    }
}
