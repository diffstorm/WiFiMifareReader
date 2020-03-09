#include<Arduino.h>

void BZR_Init();

typedef enum 
{
    NONE = 0,
    BZR_ACCESS_CONFIRMED,
    BZR_ACCESS_DENIED,
    BZR_CARD_READ_ERROR,
    BZR_CONNECTION_ERROR,
    BZR_REMOVE_CARD_ERROR
} BZR_Tone_t;


void BZR_init();

void BZR_SetAction(BZR_Tone_t action);


void BZR_Handler();