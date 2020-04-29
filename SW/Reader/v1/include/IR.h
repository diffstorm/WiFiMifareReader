#ifndef __IR_H__
#define __IR_H__

#include "types.h"

#ifdef IR_CARD_DETECT
extern void IR_Init();
extern bool IR_Handler();
#else
#define IR_Init()     ((void)0)
#define IR_Handler()  ((void)0)
#endif

#endif // __IR_H__