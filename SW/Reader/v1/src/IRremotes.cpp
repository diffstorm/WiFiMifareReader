
#include <IRremotes.h>
#include <Reader.h>

IRrecv irrecv(IRRecv_led);
IRsend irsend(IRSend_led);
decode_results results;

void IRremote_Init()
{
    irsend.begin();
    irrecv.enableIRIn();
}

obstacle_status IRremote_Handler()
{
    obstacle_status ret = NOT_FOUND;
    irsend.sendNEC(0x8804F47);
    delay(80);
    if(irrecv.decode(&results))
    {
        //serialPrintUint64(results.value,HEX);
        if(results.value == 0x8804F47)
        {
            //Serial.println("obstacle is found");
            ret = FOUND;
        }
    }
    irrecv.resume(); // Receive the next value
    return ret;

}