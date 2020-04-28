/*#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <IR.h>

IRrecv irrecv(IRRecv_led);
IRsend irsend(IRSend_led);

void IR_Init()
{
    irsend.begin();
    irrecv.enableIRIn();
}

bool IR_Handler()
{
    decode_results results;
    bool ret = false;

    irsend.sendNEC(0x8804F47);
    delay(80);
    if(irrecv.decode(&results))
    {
        //serialPrintUint64(results.value,HEX);
        if(results.value == 0x8804F47)
        {
            //Serial.println("obstacle is found");
            ret = true;
        }
    }
    irrecv.resume(); // Receive the next value

    return ret;
}*/