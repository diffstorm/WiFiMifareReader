#include <ESP8266WiFi.h>
#include "Sleep.h"
#include "RTC.h"

void Sleep_CPU(u32 interval)
{
    UTC_t utc;
    u64 t = interval;
    t *= 1000;
    utc.startvalue = interval;
    utc.utc = RTC_GetTime();
    if(false != RTC_StoreTime(utc))
    {
        ESP.deepSleep(t, RF_DISABLED);
    }
}