/* 
 * File:   myw5500.h
 * Author: hbb
 *
 * Created on August 30, 2014, 4:57 PM
 */

#ifndef MYW5500_H
#define	MYW5500_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

static const uint8_t SOCKET_1 = 0b00101;

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


void socketCommand(uint8_t socket, uint8_t command);
void openSocket(uint8_t socket);
void send(uint8_t socket);
void receive(uint8_t socket);

void setSocketMode(uint8_t socket, uint8_t mode);
void setSocketUDPMode(uint8_t socket);
void setSocketSourcePort(uint8_t socket, uint16_t port);
void setSocketDestinationPort(uint8_t socket, uint16_t port);
//void setSocketSourceIPAddress(uint8_t socket, uint32_t port);
void setSocketDestinationIPAddress(uint8_t socket, uint8_t *address);

uint8_t readSocketStatus(uint8_t socket);

#ifdef	__cplusplus
}
#endif

#endif	/* MYW5500_H */