#ifndef LED_H
#define LED_H

typedef enum 
{
    LED_ACTION_IDLE = 0,
    LED_ACTION_ACCESS_CONFIRMED,
    LED_ACTION_ACCESS_DENIED,
    LED_ACTION_CARD_READ_ERROR,
    LED_ACTION_CONNECTION_ERROR,
    LED_ACTION_REMOVE_CARD_ERROR
}LED_action_t;

void LED_init();

void LED_SetAction(LED_action_t action);


void LED_Handler();



#endif
