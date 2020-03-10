#include <Arduino.h>
#include <malloc.h>
#include <led.h>
#include "SysTick.h"

#define LED_GREEN  1   //TX
#define LED_RED   3    //RX
#define LED_DURATION 1000

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
    uint32_t t0;
    uint8_t index;
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
    {LED_GREEN,LOW,LED_DURATION},
}; 

LED_option_t LED_ACCESS_DENIED[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,LED_DURATION},
     {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,LED_DURATION},
     {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,LED_DURATION},
};

LED_option_t LED_CARD_READ_ERROR[] = 
{
    {LED_RED,HIGH,LED_DURATION},
    {LED_RED,LOW,LED_DURATION}
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

void LED_Disable()
{
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_GREEN,LOW);
}

void LED_init()
{
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_GREEN,OUTPUT);
    LED_Disable();
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
        free(led_sys);
        led_sys = NULL;
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
                led_sys->index = 0;
                led_state = LED_STATE_PERFORM;          
            }
        }
        else
        {
            break;
        }
  
    case LED_STATE_PERFORM:
        Serial.print("led pin: ");
        Serial.println(LED_sequences[led_action].option[led_sys->index].pin);
        Serial.print("led pol: ");
        Serial.println(LED_sequences[led_action].option[led_sys->index].polarity);

        LED_SetPin(LED_sequences[led_action].option[led_sys->index].pin, LED_sequences[led_action].option[led_sys->index].polarity);
        if(0 < LED_sequences[led_action].option[led_sys->index].duration)
        {
            led_sys->t0 = SysTick_get();
            led_state = LED_STATE_WAIT;
        }
        else
        {
            led_state = LED_STATE_CHECK;
            break;
        }

    case LED_STATE_WAIT:
        if(SysTick_elapsed(led_sys->t0) >= LED_sequences[led_action].option[led_sys->index].duration)
        {
            led_state = LED_STATE_CHECK;
        }
        else
        {
            break;
        }

      case LED_STATE_CHECK:
        if(led_sys->index < LED_sequences[led_action].size)
        {
            Serial.print("led index: ");
            Serial.println(led_sys->index);

            led_sys->index++;
            led_state = LED_STATE_PERFORM;
            break;
        }
        else
        {
            free(led_sys);
            led_sys = NULL;
            LED_Disable();

            Serial.println("led done");
        }
        
    default:
        led_state = LED_STATE_IDLE;
        led_action = LED_ACTION_IDLE;
        break;
    }
}
