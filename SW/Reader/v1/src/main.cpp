#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include <IRremoteESP8266.h>
#include <IRremotes.h>
#include <FS.h>
#include <Reader.h>
#include <ESPControl.h>
#include <Buzzer.h>
#include "tools.h"

extern "C" {
#include "user_interface.h"
#include <espnow.h>
}

RF_PRE_INIT()
{
    system_phy_set_powerup_option(31);  // Do full RF calibration on power-up
    system_phy_set_max_tpw(82);         // Set max TX power
}

inline void SetupBoard()
{
    pinMode(15, OUTPUT);
}

void setup()
{
    ESP.wdtDisable();
#ifdef WDT
    ESP.wdtEnable(WDTO_4S);
#endif
    SetupBoard();
#ifdef SERIAL_PORT
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.flush();
#endif
    Reader_Init();
    IRremote_Init();
    BZR_Init();
#ifdef SERIAL_PORT
    WiFi.printDiag(Serial);
    system_show_malloc();
#endif
}

void loop()
{
#ifdef WDT
    ESP.wdtFeed();
#endif

    ESP_Handler();
    BZR_Handler();
    delay(100);
}