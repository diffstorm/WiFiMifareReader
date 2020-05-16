#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__
typedef enum  // Communication channels
{
    chTCP = 0,
    chUDP,
    chSerial,
    chESPnow
} PR_Channel_t;

typedef struct __attribute__((packed)) // Data packet structure for decapsulation and encapsulation
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
}
PR_Packet_t;


bool UDPinit();
bool UDP_send(PR_Packet_t *item);
void UDP_recieve(PR_Packet_t *item);
bool UDP_fill_message_queue(PR_Packet_t item);
void send_example();

#endif