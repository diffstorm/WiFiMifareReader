#include<Arduino.h>

typedef enum 
{
    BZR_ACTION_IDLE = 0,
    BZR_ACTION_ACCESS_CONFIRMED,
    BZR_ACTION_ACCESS_DENIED,
    BZR_ACTION_CARD_READ_ERROR,
    BZR_ACTION_CONNECTION_ERROR,
    BZR_ACTION_REMOVE_CARD_ERROR
} BZR_action_t;

void BZR_Init();

void BZR_SetAction(BZR_action_t action);

void BZR_Handler();