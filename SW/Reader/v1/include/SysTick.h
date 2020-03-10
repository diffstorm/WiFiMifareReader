#ifndef SysTick_h
#define SysTick_h
#include <stdint.h>

unsigned long SysTick_getTime();
bool SysTick_checkTime(uint16_t time1,uint16_t time2);

#endif