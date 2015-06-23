/* 
 * File:   myw5500.h
 * Author: Hristo Borisov
 *
 * Created on August 30, 2014, 4:57 PM
 */

#ifndef MYW5500_H
#define	MYW5500_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

static const uint8_t UDP_HEADER_LENGTH = 8;

static const uint8_t SOCK_CLOSED = 0x00;
static const uint8_t SOCK_INIT = 0x13;
static const uint8_t SOCK_LISTEN = 0x14;
static const uint8_t SOCK_ESTABLISHED = 0x17;
static const uint8_t SOCK_CLOSE_WAIT = 0x1C;
static const uint8_t SOCK_UDP = 0x22;
static const uint8_t SOCK_MACRAW = 0x42;


static const uint8_t SOCKET_1 = 0b00101;
static const uint8_t SOCKET_1_TX_BUFFER = 0b00110;
static const uint8_t SOCKET_1_RX_BUFFER = 0b00111;
static const uint8_t SOCKET_2 = 0b01001;
static const uint8_t SOCKET_2_TX_BUFFER = 0b01010;
static const uint8_t SOCKET_2_RX_BUFFER = 0b01011;

static const uint8_t SOCKET_UDP = 0x02;
static const uint8_t SOCKET_TCP = 0x01;

static const uint8_t OPERATION_OPEN_SOCKET = 0x01;
static const uint8_t OPERATION_LISTEN_SOCKET = 0x02;
static const uint8_t OPERATION_CONNECT_SOCKET = 0x04;
static const uint8_t OPERATION_DISCON_SOCKET = 0x08;
static const uint8_t OPERATION_CLOSE_SOCKET = 0x10;
static const uint8_t OPERATION_SEND_SOCKET = 0x20;
static const uint8_t OPERATION_SEND_MAC_SOCKET = 0x21;
static const uint8_t OPERATION_SEND_KEEP_SOCKET = 0x22;
static const uint8_t OPERATION_RECV_SOCKET = 0x40;

struct UDPHeader {
    uint8_t destinationIPAddressByte1;
    uint8_t destinationIPAddressByte2;
    uint8_t destinationIPAddressByte3;
    uint8_t destinationIPAddressByte4;
    uint16_t destinationPort;
    uint16_t dataLength;
};

void socketCommand(uint8_t socket, uint8_t command);
void openSocket(uint8_t socket);
void closeSocket(uint8_t socket);
void listen(uint8_t socket);
void send(uint8_t socket);
void receive(uint8_t socket);
void connect(uint8_t socket);
void disconnect(uint8_t socket);
void close(uint8_t socket);

void setSocketMode(uint8_t socket, uint8_t mode);
void setSocketUDPMode(uint8_t socket);
void setSocketTCPMode(uint8_t socket);
void setSocketSourcePort(uint8_t socket, uint16_t port);
void setSocketDestinationPort(uint8_t socket, uint16_t port);
void setSocketDestinationIPAddress(uint8_t socket, uint8_t *address);

uint8_t readSocketStatus(uint8_t socket);
uint8_t readSocketInterruptRegister(uint8_t socket);
uint16_t readNumberOfBytesReceived(uint8_t socket);
uint16_t readWritePointer(uint8_t socket);
uint16_t readReadPointer(uint8_t socket);
void increaseWritePointer(uint8_t socket, uint16_t len);
void increaseReadPointer(uint8_t socket, uint16_t len);
void writeToSocketTxBuffer(uint8_t socketTxBuffer, uint16_t writePointer, unsigned char* data);
uint16_t readFromSocketRxBuffer(uint8_t socketRxBuffer, uint16_t readPointer, unsigned char *buffer);
void readFromSocketRxBufferLen(uint8_t socketRxBuffer, uint16_t readPointer, unsigned char *buffer, uint16_t len);
uint16_t readTxFreeSize(uint8_t socket);

void clearInterrupts(uint8_t socket);

#ifdef	__cplusplus
}
#endif

#endif	/* MYW5500_H */