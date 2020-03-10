#include "SysTick.h"
#include <Arduino.h>

bool SysTick_checkTime(uint16_t time1,uint16_t time2)
{
    return time1 < time2 ;
}

unsigned long SysTick_getTime()
{
    return millis();
}