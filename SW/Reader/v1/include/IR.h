#ifndef __IR_H__
#define __IR_H__

#define IRSend_led  0
#define IRRecv_led  2

extern void IR_Init();
extern bool IR_Handler();

#endif // __IR_H__