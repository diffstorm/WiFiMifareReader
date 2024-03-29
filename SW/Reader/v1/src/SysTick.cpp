
#include <Arduino.h>
#include "SysTick.h"

//! Time difference between 2 epoc value including overflow math
u32 TimeDiff(u32 t0, u32 t1)
{
    u32 dt;
    if(t1 < t0)
    {
        t1 = (0xFFFFFFFF - t0) + t1;
        t0 = 0;
    }
    dt = t1 - t0;
    return dt;
}

u32 SysTick_elapsed(u32 t0)
{
    return TimeDiff(t0, SysTick_get());
}

u32 SysTick_get()
{
    return millis();
}
