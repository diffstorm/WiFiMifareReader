#include <Arduino.h>
#include <MFRC522.h>
#include <IRremoteESP8266.h>
#include <IRremotes.h>
#include <Reader.h>
#include <ESPControl.h>
#include<Buzzer.h>
bool ret=false;
void setup() {
  Serial.begin(115200);       
  pinMode(15,OUTPUT);
  Reader_Init();
  IRremote_Init();
  BZR_Init();
  
  
   Serial.println("setup init");
}

void loop() {
  Serial.println("TEST");
  ESP_Handler();
  BZR_Handler();
  delay(100);
}