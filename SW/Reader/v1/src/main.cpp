#include <Arduino.h>
#include <MFRC522.h>
#include <IRremoteESP8266.h>
#include <IRremotes.h>
#include <Reader.h>
#include <ESPControl.h>
#include <led.h>

int *ptr1;
int *ptr2;
int x =5 ;

int* str[] = 
{
  ptr1,
  ptr2,
};

bool ret=false;
void setup() {
  Serial.begin(115200);       
  pinMode(15,OUTPUT);
  Reader_Init();
  IRremote_Init();
   Serial.println("setup init");
}

void loop() {
  //deneme
  ESP_Handler();
  delay(100);
}