#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "types.h"
extern "C" {
#include "user_interface.h"
}

typedef enum // Communication channels
{
    chTCP = 0,
    chUDP,
    chSerial
} PR_Channel_t;

typedef struct // Data packet structure for decapsulation and encapsulation
{
    PR_Channel_t channel;	// communication channel
    union  					// port is used for udp remoteport where index is not necessary and vise versa
    {
        u16 index;			// tcp index
        u16 port;			// udp port
    };
    IPAddress *ip;			// target ip address (can be null)
    u16 length;			    // length of data
    unsigned char *buffer;	// data buffer
} PR_Packet_t;

#endif // __PROTOCOL_H__