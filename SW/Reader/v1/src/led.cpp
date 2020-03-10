#include <Arduino.h>
#include <malloc.h>
#include <led.h>
#include "SysTick.h"

#define LED_GREEN  15   //D3 GPIOA   0 
#define LED_RED   A0    //D4 GPIOA2   2 
#define LED_DURATION 2

typedef enum
{
    LED_STATE_IDLE = 0,
    LED_STATE_PERFORM,
    LED_STATE_WAIT,
    LED_STATE_CHECK
} LED_state_t;        

typedef struct
{
    uint8_t pin;
    boolean polarity;
    uint16_t duration;
} LED_option_t;

typedef struct
{
    LED_option_t *option;
    size_t size;
} LED_sequence_t;

typedef struct
{
    uint16_t current_time;
    uint8_t timer_id;
    uint8_t index;
    bool timeout;
} LED_sys_t;

// Global variables
LED_state_t led_state;
LED_action_t led_action;

// Local variables
LED_sys_t *led_sys;

LED_option_t LED_IDLE[] = 
{
    {LED_RED,LOW,LED_DURATION}
};

LED_option_t LED_ACCESS_CONFIRMED[] = 
{
    {LED_GREEN,HIGH,LED_DURATION},
    {LED_GREEN,LOW,0}
}; 

LED_option_t LED_ACCESS_DENIED[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,0}
};

LED_option_t LED_CARD_READ_ERROR[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,0}
};

LED_option_t LED_CONNECTION_ERROR[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,0}
};

LED_option_t LED_REMOVE_CARD_ERROR[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,0}
};

const LED_sequence_t LED_sequences[] = 
{
    {LED_IDLE, sizeof(LED_IDLE) / sizeof(LED_option_t)},
    {LED_ACCESS_CONFIRMED, sizeof(LED_ACCESS_CONFIRMED) / sizeof(LED_option_t)},
    {LED_ACCESS_DENIED, sizeof(LED_ACCESS_DENIED) / sizeof(LED_option_t)},
    {LED_CARD_READ_ERROR, sizeof(LED_CARD_READ_ERROR) / sizeof(LED_option_t)},
    {LED_CONNECTION_ERROR, sizeof(LED_CONNECTION_ERROR) / sizeof(LED_option_t)},
    {LED_REMOVE_CARD_ERROR, sizeof(LED_REMOVE_CARD_ERROR) / sizeof(LED_option_t)}
};

void LED_init()
{
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_GREEN,OUTPUT);
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_GREEN,LOW);
    led_state = LED_STATE_IDLE;
    led_action = LED_ACTION_IDLE;
    led_sys = NULL;
}

void LED_SetAction(LED_action_t action)
{
    led_action = action;
    led_state = LED_STATE_IDLE;
    if(NULL != led_sys)
    {
        led_sys->current_time = 0;
        free(led_sys);
        led_sys = NULL;
    }
}
void LED_TimerCallback()
{
    if(NULL != led_sys)
    {
        led_sys->timeout = true;
    }
}

void LED_SetPin(uint8_t pin, uint8_t polarity)
{
    digitalWrite(pin, polarity);
}

void LED_Handler()
{
    switch (led_state)
    {
    case LED_STATE_IDLE:
        if(LED_ACTION_IDLE != led_action)
        {
            led_sys = (LED_sys_t*)malloc(sizeof(LED_sys_t));
            if(NULL != led_sys)
            {
                led_sys->index = 0;                     //görev sırası
                led_state = LED_STATE_PERFORM;          
            }
        }
        else
        {
            break;
        }
  
    case LED_STATE_PERFORM:
        LED_SetPin(LED_sequences[led_action].option[led_sys->index].pin, LED_sequences[led_action].option[led_sys->index].polarity);
        if(0 < LED_sequences[led_action].option[led_sys->index].duration)
        {
            led_sys->timeout = false; 
            led_sys->current_time = SysTick_getTime();
            if(false != SysTick_checkTime(LED_sequences[led_action].option[led_sys->index].duration,led_sys->current_time))
            {
                led_sys -> timeout =true;
                led_sys ->current_time = 0;
            }
                led_state = LED_STATE_WAIT;
        }
        else
        {
            led_state = LED_STATE_CHECK;
            break;
        }

    case LED_STATE_WAIT:
        if(false != led_sys->timeout)
        {
            led_state = LED_STATE_CHECK;
        }
        else
        {
            break;
        }
      case LED_STATE_CHECK:
        Serial.println("led state check");
        if(led_sys->index < LED_sequences[led_action].size)
        {
            led_sys->index++;
            led_state = LED_STATE_PERFORM;
            break;
        }
        else
        {
             Serial.println("gorev bitti");
            free(led_sys);
            led_sys = NULL;
        }
    default:
        led_state = LED_STATE_IDLE;
        led_action = LED_ACTION_IDLE;
        break;
    }
}

