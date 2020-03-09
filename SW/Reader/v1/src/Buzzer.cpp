
#include <malloc.h>
#include <Timer.h>
#include "Buzzer.h"
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
    Timer timer;
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
        if(0 <= BZR_sys->timer_id)
        {
            BZR_sys->timer.stop(BZR_sys->timer_id);
            BZR_sys->timer_id = -1;
        }
        free(BZR_sys);
        BZR_sys = NULL;
    }
}

void BZR_Set_Pin(uint8_t BZR_pin, bool polarity)
{
    digitalWrite(BZR_pin, polarity);
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
}

void BZR_Handler()
{
    switch(BZR_State)
    {
    case BZR_STATE_IDLE:
        if(NONE!= BZR_action)
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
            Serial.println("none geldi");
            digitalWrite(buzzerPin,LOW);
            break;
        }

    case BZR_STATE_PERFORM:
        BZR_Set_frequency(Tones[BZR_action].tone[BZR_sys->index].frequency);
        BZR_Set_Pin(Tones[BZR_action].tone[BZR_sys->index].pin, Tones[BZR_action].tone[BZR_sys->index].polarity);
        Serial.println("gorev geldi");
        if(0 < Tones[BZR_action].tone[BZR_sys->index].duration)
        {
            BZR_sys->timeout=false;
            BZR_sys->timer_id = BZR_sys->timer.after((Tones[BZR_action].tone[BZR_sys->index].duration), BZR_TimerCallback);
            if(0 <= BZR_sys->timer_id)
            {
                BZR_State=BZR_STATE_IDLE;
            }
        }
        else
        {
            BZR_State=BZR_STATE_CHECK;
            break;
        }
    case BZR_STATE_WAIT:
        BZR_sys->timer.update();
        if (false != BZR_sys->timeout)
        {
            BZR_sys->timer.stop(BZR_sys->timer_id);
            BZR_sys->timer_id=-1;
            BZR_State=BZR_STATE_CHECK;
        }
        else
        {
            break;
        }
    case BZR_STATE_CHECK:
        if(BZR_sys->index < Tones[BZR_action].size)
        {
            BZR_sys->index++;
            BZR_State=BZR_STATE_PERFORM;
            break;
        }
        else
        {
            free(BZR_sys);
            BZR_sys=NULL;
        }

        default:
        BZR_State = BZR_STATE_IDLE;
        BZR_action = NONE;
        break;
    }
}


    








