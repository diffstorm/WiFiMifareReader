
#include <malloc.h>
#include "Buzzer.h"
#include "SysTick.h"

#define buzzerPin 15 // GPIO15

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
    uint16_t duration;
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
    {c, 0}
};

BZR_option_t Tone_ACCESS_CONFIRMED[] =
{
    {b, 10},
    {0, 10},
    {b, 10},
    {0, 10}
};

BZR_option_t Tone_ACCESS_DENIED[] =
{
    {cSH, 100},
    {0, 600},
    {cSH, 100},
    {0, 600},
    {cSH, 100},
    {0, 600},
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
    {fH, 500},
    {0, 500},
    {dSH, 500},
    {0, 500},
};

BZR_option_t Tone_REMOVE_CARD_ERROR[] =
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

BZR_sequence_t Tones[] =
{
    {Tone_NoTone, (sizeof(Tone_NoTone) / sizeof(BZR_option_t))},
    {Tone_ACCESS_CONFIRMED, (sizeof(Tone_ACCESS_CONFIRMED) / sizeof(BZR_option_t))},
    {Tone_CARD_READ_ERROR, (sizeof(Tone_CARD_READ_ERROR) / sizeof(BZR_option_t))},
    {Tone_CONNECTION_ERROR, (sizeof(Tone_CONNECTION_ERROR) / sizeof(BZR_option_t))},
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
    os_intr_lock();
    analogWriteRange(PWMRANGE);
    analogWriteFreq(frequency); // [Hz]
    analogWrite(buzzerPin, PWMRANGE / 2); // Duty : 50%
    os_intr_unlock();
    yield();
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
        Serial.print("Nota freq: ");
        Serial.println(Tones[BZR_action].tone[BZR_sys->index].frequency);

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
        if (BZR_sys->index < Tones[BZR_action].size)
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
