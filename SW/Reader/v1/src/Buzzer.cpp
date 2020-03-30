#include <malloc.h>
#include "Buzzer.h"
#include "SysTick.h"

#define buzzerPin 15 // GPIO15

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

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
    uint16_t frequency;
    u32 duration;
} BZR_option_t;

typedef struct
{
    BZR_option_t *tone;
    size_t size;
} BZR_sequence_t;

typedef struct
{
    uint32_t t0;
    uint8_t index;
} BZR_sys_t;

BZR_action_t BZR_action;
BZR_state_t BZR_state;
BZR_sys_t *BZR_sys;

BZR_option_t Tone_NoTone[] =
{
    {0, 0}
};

BZR_option_t Tone_ACCESS_CONFIRMED[] =
{
    {NOTE_C4, 50},
    {NOTE_C3, 25},
    {NOTE_C3, 25},
    {NOTE_A3, 50},
    {NOTE_G3, 50},


};

BZR_option_t Tone_ACCESS_DENIED[] =
{
    {NOTE_C4, 500},
    {NOTE_C3, 250},
    {NOTE_C3, 250},
    {NOTE_A3, 500},
    {NOTE_G3, 500},
    {0, 500},
    {NOTE_B3, 500},
    {NOTE_C4, 500},
};

BZR_option_t Tone_CARD_READ_ERROR[] =
{
    {b, 500},
    {0, 500},
    {gH, 500},
    {0, 500},
    {fH, 500},
    {0, 500},
    {dSH, 500},
    {0, 500},
};

BZR_option_t Tone_CONNECTION_ERROR[] =
{
    {b, 500},
    {0, 500},
    {gH, 500},
    {0, 500},
    {a, 500},
    {0, 500},
    {b, 500},
    {0, 500},
};

BZR_option_t Tone_REMOVE_CARD_ERROR[] =
{
    {b, 500},
    {0, 500},
    {c, 500},
    {0, 500},
    {fH, 500},
    {0, 500},
    {d, 500},
    {0, 500},
};

BZR_sequence_t Tones[] =   // TODO Obstacle detacted for long time
{
    {Tone_NoTone, (sizeof(Tone_NoTone) / sizeof(BZR_option_t))},
    {Tone_ACCESS_CONFIRMED, (sizeof(Tone_ACCESS_CONFIRMED) / sizeof(BZR_option_t))},
    {Tone_ACCESS_DENIED, (sizeof(Tone_ACCESS_DENIED) / sizeof(BZR_option_t))},
    {Tone_CARD_READ_ERROR, (sizeof(Tone_CARD_READ_ERROR) / sizeof(BZR_option_t))},
    {Tone_CONNECTION_ERROR, (sizeof(Tone_CONNECTION_ERROR) / sizeof(BZR_option_t))},
    {Tone_REMOVE_CARD_ERROR, (sizeof(Tone_REMOVE_CARD_ERROR) / sizeof(BZR_option_t))}
};


void BZR_Disable()
{
    
    os_intr_lock();
    analogWrite(buzzerPin, 0);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    os_intr_unlock();
    yield();
}

void BZR_Set_frequency(uint16_t frequency)
{
    
    if(0==frequency)
    {   
        BZR_Disable();
    }
    else
    {
        os_intr_lock();
        analogWriteRange(PWMRANGE);
        analogWriteFreq(frequency); // [Hz]
        analogWrite(buzzerPin, PWMRANGE / 2);  // Duty : 50%
        os_intr_unlock();
        yield();
    }
}

void BZR_Init()
{
    BZR_Disable();
    BZR_state = BZR_STATE_IDLE;
    BZR_action = BZR_ACTION_IDLE;
    BZR_sys = NULL;
}

void BZR_SetAction(BZR_action_t action)
{
    BZR_action = action;
    BZR_state = BZR_STATE_IDLE;
    if (NULL != BZR_sys)
    {
        free(BZR_sys);
        BZR_sys = NULL;
    }
}

void BZR_Handler()
{
    switch (BZR_state)
    {
    case BZR_STATE_IDLE:
        if (BZR_ACTION_IDLE != BZR_action)
        {
            BZR_sys = (BZR_sys_t *)malloc(sizeof(BZR_sys_t));
            if (NULL != BZR_sys)
            {
                BZR_sys->index = 0;
                BZR_state = BZR_STATE_PERFORM;
            }
        }
        else
        {
            break;
        }

    case BZR_STATE_PERFORM:
        //Serial.print("Nota freq: ");
        //Serial.println(Tones[BZR_action].tone[BZR_sys->index].frequency);
        //BZR_Disable();
        delay(10);
        BZR_Set_frequency(Tones[BZR_action].tone[BZR_sys->index].frequency);
        if (0 < Tones[BZR_action].tone[BZR_sys->index].duration)
        {
            BZR_sys->t0 = SysTick_get();
            BZR_state = BZR_STATE_WAIT;
        }
        else
        {
            BZR_state = BZR_STATE_CHECK;
            break;
        }

    case BZR_STATE_WAIT:
        if (SysTick_elapsed(BZR_sys->t0) >= Tones[BZR_action].tone[BZR_sys->index].duration)
        {
            BZR_state = BZR_STATE_CHECK;
        }
        else
        {
            break;
        }

    case BZR_STATE_CHECK:
        if (BZR_sys->index < Tones[BZR_action].size -1)
        {
            Serial.print("Nota index: ");
            Serial.println(BZR_sys->index);

            BZR_sys->index++; 
            BZR_state = BZR_STATE_PERFORM;
            
            break;
        }
        else
        {
            free(BZR_sys);
            BZR_sys = NULL;
            BZR_Disable();

            Serial.println("buzzer done");
        }

    default:
        BZR_state = BZR_STATE_IDLE;
        BZR_action = BZR_ACTION_IDLE;
        break;
    }
}