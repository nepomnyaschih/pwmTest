#include <Arduino.h>

int IN_PIN = 34;
int OUT_PIN = 2;

int currentState = true;

int arrayValue[100];
int iterator=0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Start...");

  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);
}

void loop() {

int val = analogRead(IN_PIN);

if (iterator>=99) {
  iterator = 0;
  Serial.println(arrayValue[0]);
}

arrayValue[iterator] = val;

iterator++;

currentState= !currentState;
digitalWrite(OUT_PIN, currentState);
}
