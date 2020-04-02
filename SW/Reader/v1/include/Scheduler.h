#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "types.h"

typedef enum
{
    task_idle = 0, // User to add tasks here
    task_Card,
    task_WiFi,
    task_UDP,
    task_Web,
    task_Log,
    task_end
} Tasks_t;

extern void Scheduler_SetPeriod(Tasks_t task, u32 period);
extern u32  Scheduler_GetPeriod(Tasks_t task);
extern bool Scheduler_GetEvent(Tasks_t task);
extern void Scheduler_ForceEvent(Tasks_t task);
extern void Scheduler_ForceAllEvents();
extern void Scheduler_ClearEvent(Tasks_t task);
extern void Scheduler_ClearAllEvents();

extern void Scheduler_Init(bool force);
extern void Scheduler_Handler();

#endif // __SCHEDULER_H__
