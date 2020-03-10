
#include <malloc.h>
#include "Buzzer.h"
#include "SysTick.h"
#define buzzerPin 15

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;


typedef enum
{
    BZR_STATE_IDLE = 0,
    BZR_STATE_PERFORM,
    BZR_STATE_WAIT,
    BZR_STATE_CHECK
} BZR_state_t;        

typedef struct 
{
    uint8_t pin;
    uint16_t frequency;
    uint16_t duration;
    bool polarity;
} BZR_Note_t;


typedef struct
{
    BZR_Note_t *tone;
    size_t size;
} BZR_Tones_t;

typedef struct
{
    uint16_t current_time;
    int8_t timer_id;
    uint8_t index;
    bool timeout;
} BZR_sys_t;

BZR_Note_t Tone_NoTone[] = 
{
    {buzzerPin, c, 0,LOW}
};

BZR_Note_t Tone_ACCESS_CONFIRMED[] = 
{
    {buzzerPin,b, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,gH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,fH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,dSH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
};

BZR_Note_t Tone_ACCESS_DENIED[] = 
{
    {buzzerPin,b, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,gH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,fH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,dSH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
};

BZR_Note_t Tone_CARD_READ_ERROR[] = 
{
    {buzzerPin,b, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,gH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,fH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,dSH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
};

BZR_Note_t Tone_CONNECTION_ERROR[] = 
{
    {buzzerPin,b, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,gH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,fH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,dSH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
};

BZR_Note_t Tone_REMOVE_CARD_ERROR[] = 
{
    {buzzerPin,b, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,gH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,fH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
    {buzzerPin,dSH, 500, HIGH},
    {buzzerPin,0, 500, LOW},
};

BZR_Tone_t BZR_action;
BZR_state_t BZR_State;
BZR_sys_t *BZR_sys;


BZR_Tones_t Tones[] = 
{
     
    {Tone_NoTone,(sizeof(Tone_NoTone) / sizeof(BZR_Note_t))},
    {Tone_ACCESS_CONFIRMED,(sizeof(Tone_ACCESS_CONFIRMED) / sizeof(BZR_Note_t))},
    {Tone_CARD_READ_ERROR,(sizeof(Tone_CARD_READ_ERROR) / sizeof(BZR_Note_t))},
    {Tone_CONNECTION_ERROR,(sizeof(Tone_CONNECTION_ERROR) / sizeof(BZR_Note_t))},
    {Tone_CONNECTION_ERROR,(sizeof(Tone_CONNECTION_ERROR) / sizeof(BZR_Note_t))},
    {Tone_REMOVE_CARD_ERROR,(sizeof(Tone_REMOVE_CARD_ERROR) / sizeof(BZR_Note_t))}
}; 





void BZR_Init()
{
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    analogWriteRange(255);
    analogWriteFreq(100);
    analogWrite(buzzerPin,0);
    
}
void BZR_SetAction(BZR_Tone_t BZR_tone)
{
    BZR_action=BZR_tone;
    BZR_State=BZR_STATE_IDLE;
    if(NULL != BZR_sys)
    {
        BZR_sys -> current_time = 0;
        free(BZR_sys);
        BZR_sys = NULL;
    }
}

void BZR_Set_Pin(uint8_t BZR_pin, bool polarity)
{
    digitalWrite(BZR_pin, polarity);
    analogWrite(buzzerPin,255);
}

void BZR_Set_frequency(uint16_t frequency)
{
    os_intr_lock();
    analogWriteFreq(frequency);
    os_intr_unlock();
    yield();
}

void BZR_TimerCallback()
{
    BZR_sys->timeout=true;
    Serial.println("timer ++");
}

void BZR_Handler()
{
   

    switch(BZR_State)
    {
    case BZR_STATE_IDLE:
        if(BZR_NONE!= BZR_action)
        {
            BZR_sys=(BZR_sys_t*)malloc(sizeof(BZR_sys_t));
            if(NULL != BZR_sys)
            {
                BZR_sys->index=0;
                BZR_State=BZR_STATE_PERFORM;

            }
        }
        else
        {
            digitalWrite(buzzerPin,LOW);
            break;
        }

    case BZR_STATE_PERFORM:
        delay(20);
        BZR_Set_frequency(Tones[BZR_action].tone[BZR_sys->index].frequency);
        BZR_Set_Pin(Tones[BZR_action].tone[BZR_sys->index].pin, Tones[BZR_action].tone[BZR_sys->index].polarity);
        Serial.println("gorev geldi");
        if(0 < Tones[BZR_action].tone[BZR_sys->index].duration)
        {
            BZR_sys->timeout=false;
            BZR_sys->current_time = SysTick_getTime();
            if(false != SysTick_checkTime((Tones[BZR_action].tone[BZR_sys->index].duration),BZR_sys->current_time))
            {
                BZR_sys->timeout = true;
                BZR_sys->current_time = 0;
            }
            BZR_State=BZR_STATE_WAIT;
        }
        else
        {
            BZR_State=BZR_STATE_CHECK;
            break;
        }
    case BZR_STATE_WAIT:
        if (false != BZR_sys->timeout)
        {
            BZR_State=BZR_STATE_CHECK;
        }
        else
        {
            break;
        }
    case BZR_STATE_CHECK:
        if(BZR_sys->index < Tones[BZR_action].size)
        {
            
            Serial.println(Tones[BZR_action].size);
            Serial.print("Nota index: ");
            Serial.println(BZR_sys->index);
            BZR_sys->index++;
            BZR_State=BZR_STATE_PERFORM;
            
            Serial.print("Nota index arttırılmıs: ");
            Serial.print(BZR_sys->index);
            break;
        }
        else
        {
            free(BZR_sys);
            Serial.println("buzzer gorevi tamamlandi");
            //BZR_sys=NULL;
            break;
            //flag=false;
            
        }

        default:
        BZR_State = BZR_STATE_IDLE;
        BZR_action = BZR_NONE;
        break;
    }
}








