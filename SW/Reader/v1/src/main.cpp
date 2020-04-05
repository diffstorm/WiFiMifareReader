#include <ESP8266WiFi.h>
#include <FS.h>
#include "Reader.h"
#include "Buzzer.h"
#include "IR.h"
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
#ifdef IR_CARD_DETECT
    IR_Init();
#endif
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

    BZR_Handler();
    delay(100);
}