#include <Arduino.h>
#include <DebugLog.h>

void DBG_LOG_Init(unsigned long baudrate)
{
    Serial.begin(baudrate);
}

// Printout: message [int, float, double, hex] | <function_name> @ <file_name> : <line>
void DBG_LOG(const char *message, const char *func, const char *loc, int *i, float *f, double *d, char *hex, int hex_size)
{
    Serial.print(message);
    if(NULL != i)
    {
        Serial.print(" ");
        Serial.print(*i);
    }
    else if(NULL != f)
    {
        Serial.print(" ");
        Serial.print(*f);
    }
    else if(NULL != d)
    {
        Serial.print(" ");
        Serial.print(*d);
    }
    else if(NULL != hex && 0 < hex_size)
    {
        Serial.print(" [");
        for(int i = 0; i < hex_size; i++)
        {
            Serial.printf("%02X", hex[i]);

            if(i + 1 < hex_size)
            {
                Serial.print(", ");
            }
        }
        Serial.print("]");
    }
    Serial.print(" | ");
    Serial.print(func);
    Serial.println(loc);
}
