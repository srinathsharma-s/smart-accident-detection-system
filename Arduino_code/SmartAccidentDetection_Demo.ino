/*
 SmartAccidentDetection.ino
 Demonstration template for UI/sensor logic only.
 This sketch intentionally DOES NOT implement GSM SMS/call functionality.
*/

#include <Wire.h>

const int vibrationPin = 2;
const int buzzerPin = 9;
const int cancelButton = 10;
const int redLED = 11;
const int greenLED = 12;

bool countdown = false;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(cancelButton, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(greenLED, HIGH);
  Serial.println("Smart Accident Detection Demo");
}

void loop() {
  if (!countdown && digitalRead(vibrationPin) == HIGH) {
    countdown = true;
    startTime = millis();
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    Serial.println("Impact detected. Starting 15 second countdown...");
  }

  if (countdown) {
    tone(buzzerPin, 1000);

    if (digitalRead(cancelButton) == LOW) {
      noTone(buzzerPin);
      countdown = false;
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      Serial.println("Alert cancelled.");
      delay(500);
    } else {
      unsigned long elapsed = (millis() - startTime) / 1000;
      if (elapsed >= 15) {
        noTone(buzzerPin);
        Serial.println("Countdown complete.");
        Serial.println("GPS: <placeholder latitude>, <placeholder longitude>");
        Serial.println("Alert would be generated here.");
        countdown = false;
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
      }
    }
  }
}
