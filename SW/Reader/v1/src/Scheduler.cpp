#include "Scheduler.h"
#include "SysTick.h"

#define SCHEDULER_TASK_SIZE (task_end - task_idle - 1)

#define WAIT_UNTIL_CLEARED  1 // 0 : disabled | 1 : enabled
#define TASK_PARAM_CHECK    1 // 0 : disabled | 1 : enabled

#if TASK_PARAM_CHECK
#define PARAM_VALIDATE()  if(task_idle < task && task_end > task)
#else
#define PARAM_VALIDATE()
#endif

u32 taskperiods[SCHEDULER_TASK_SIZE] =
{
    200, // task_Card
    4000,// task_WiFi
    100, // task_UDP
    250, // task_Web
    9000 // task_Log
};

u32 timeanchors[SCHEDULER_TASK_SIZE];
bool taskevents[SCHEDULER_TASK_SIZE];

void Scheduler_SetPeriod(Tasks_t task, u32 period)
{
    PARAM_VALIDATE()
    {
        taskperiods[task - 1] = period;
    }
}

u32 Scheduler_GetPeriod(Tasks_t task)
{
    u32 ret = 0;

    PARAM_VALIDATE()
    {
        ret = taskperiods[task - 1];
    }

    return ret;
}

bool Scheduler_GetEvent(Tasks_t task)
{
    bool ret = false;

    PARAM_VALIDATE()
    {
        ret = taskevents[task - 1];
    }

    return ret;
}

void Scheduler_ForceEvent(Tasks_t task)
{
    PARAM_VALIDATE()
    {
        taskevents[task - 1] = true;
    }
}

void Scheduler_ForceAllEvents()
{
    Scheduler_Init(true);
}

void Scheduler_ClearEvent(Tasks_t task)
{
    PARAM_VALIDATE()
    {
        taskevents[task - 1] = false;
        timeanchors[task - 1] = SysTick_get();
    }
}

void Scheduler_ClearAllEvents()
{
    Scheduler_Init(false);
}

void Scheduler_Init(bool force)
{
    u16 i;

    for(i = 0; i < task_end - 1; i++)
    {
        taskevents[i] = force;
        timeanchors[i] = SysTick_get();
    }
}

void Scheduler_Handler()
{
    u16 i;

    for(i = 0; i < task_end - 1; i++)
    {
#if WAIT_UNTIL_CLEARED
        if(false == taskevents[i])
#endif
        {
            if(SysTick_elapsed(timeanchors[i]) >= taskperiods[i])
            {
                taskevents[i] = true;
            }
        }
    }
}

void example()
{
    static u8 wifi_counter = 0;
    Scheduler_Init(false);

    // Change task period
    Scheduler_SetPeriod(task_WiFi, 2000);
    // Force task execution
    Scheduler_ForceEvent(task_WiFi);

    for(;;)
    {
        Scheduler_Handler();
        if(Scheduler_GetEvent(task_WiFi))
        {
            Scheduler_ClearEvent(task_WiFi);
            // Call WiFi function
            if(++wifi_counter > 50)
            {
                if(4000 > Scheduler_GetPeriod(task_WiFi))
                {
                    Scheduler_SetPeriod(task_WiFi, 4000);
                    wifi_counter = 0;
                }
            }
        }
    }
}