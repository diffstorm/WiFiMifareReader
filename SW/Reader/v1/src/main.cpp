#include <Arduino.h>
#include <MFRC522.h>
#include <IRremoteESP8266.h>
#include <IRremotes.h>
#include <Reader.h>
#include <ESPControl.h>
#include<Buzzer.h>
//#include <led.h>
bool ret=false;
void setup() {
  Serial.begin(115200);       
  pinMode(15,OUTPUT);
  Reader_Init();
  IRremote_Init();
  //LED_init();
  BZR_Init();
  
  
   Serial.println("setup init");
}

void loop() {
  ESP_Handler();
  BZR_Handler();
  //LED_Handler();
  delay(100);
}