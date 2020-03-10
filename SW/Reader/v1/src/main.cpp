#include <Arduino.h>
#include <IRremotes.h>
#include <Reader.h>
#include <ESPControl.h>
#include <Buzzer.h>
#include <led.h>

void setup() {
  Serial.begin(115200);       
  pinMode(15,OUTPUT);
  Reader_Init();
  IRremote_Init();
  //LED_init();
  BZR_Init();
   //Serial.println("setup init");
}

void loop() {
  ESP_Handler();
  BZR_Handler();
  //LED_Handler();
  delay(100);
}