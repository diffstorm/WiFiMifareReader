#include <ESPControl.h>
#include <IRremotes.h>
#include <Reader.h>
#include<Buzzer.h>


void ledYak()
{
     digitalWrite(15,HIGH);
     delay(250);
     digitalWrite(15,LOW);
}

void ESP_Handler()
{
     obstacle_status ret = IRremote_Handler();
     //bool status = true;
     if (NOT_FOUND != ret)
     {
          //Serial.println("esp wake up");
          Reader_WakeUp();
          if (false != READER_handler())
          {
          
          Serial.println("kart eslesti kapi acildi");
          
            //status=false;
            //ledYak();
          }
     
          
     }
     else
     {
          //Serial.println("esp sleep mode");
          Reader_Sleep();
          //ESP.deepSleep(10000000); //sleep for 2second
     }
}
