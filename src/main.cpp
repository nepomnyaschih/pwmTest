#include <Arduino.h>

int IN_PIN = 34;
int OUT_PIN = 2;

int OUT_SIN_PIN = 25; //is this without pwm modulation? https://esp-idf.readthedocs.io/en/v2.0/api/peripherals/dac.html

int currentState = true;

int arrayValue[100];
int iterator=0;

void firstCoreTask( void * pvParameters ){
    while(true){

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
}

void secondCoreTask( void * pvParameters ){
    while(true){
        dacWrite(OUT_SIN_PIN, random(0, 255));
    }
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Start...");

  pinMode(OUT_PIN, OUTPUT);
  pinMode(OUT_SIN_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);


  xTaskCreatePinnedToCore(
                    firstCoreTask,   /* Function to implement the task */
                    "firstCoreTask", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    0,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    0);  /* Core where the task should run */
}

void loop() {
  dacWrite(OUT_SIN_PIN, random(0, 255));
  delay(1);
}
