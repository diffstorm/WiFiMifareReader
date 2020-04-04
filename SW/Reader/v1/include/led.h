#ifndef __LED_H__
#define __LED_H__

typedef enum
{
    LED_ACTION_IDLE = 0,
    LED_ACTION_ACCESS_CONFIRMED,
    LED_ACTION_ACCESS_DENIED,
    LED_ACTION_CARD_READ_ERROR,
    LED_ACTION_CONNECTION_ERROR,
    LED_ACTION_REMOVE_CARD_ERROR
} LED_action_t;

extern void LED_init();
extern void LED_SetAction(LED_action_t action);
extern void LED_Handler();

#endif // __LED_H__
