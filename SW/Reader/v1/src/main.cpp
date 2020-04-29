#include <ESP8266WiFi.h>
#include <FS.h>
#include "Reader.h"
#include "Buzzer.h"
#include "IR.h"
#include "tools.h"
#include "FileSystem.h"
#include "whitelist.h"

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
    ESP.wdtEnable(WDTO_8S);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.flush();
#endif
    LOG_Init(115200);
    Reader_Init();
#ifdef IR_CARD_DETECT
    IR_Init();
#endif
    BZR_Init();
#ifdef SERIAL_PORT
    WiFi.printDiag(Serial);
    system_show_malloc();
#endif
    LOGp("Testing %d and %f also %s", 123, 12.3, "this");
}
static bool testdone = false;

void loop()
{

    ESP.wdtFeed();
    if(false == testdone)
    {
        Serial.println("sa");
        example_whitelist();
        testdone = true;
    }
}

/*
#ifdef WDT
ESP.wdtFeed();
#endif

BZR_Handler();
delay(100);

} */