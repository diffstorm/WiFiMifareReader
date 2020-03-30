#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#define IRSend_led  0 
#define IRRecv_led  2

typedef enum{
    FOUND,
    NOT_FOUND
}obstacle_status;

void IRremote_Init();
obstacle_status IRremote_Handler();


void IRremote_Init();


