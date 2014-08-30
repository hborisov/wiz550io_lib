/* 
 * File:   myw5500.h
 * Author: hbb
 *
 * Created on August 30, 2014, 4:57 PM
 */

#ifndef MYW5500_H
#define	MYW5500_H

#ifdef	__cplusplus
extern "C" {
#endif

static const unsigned char OPERATION_OPEN_SOCKET = 0x01;
static const unsigned char OPERATION_LISTEN_SOCKET = 0x02;
static const unsigned char OPERATION_CONNECT_SOCKET = 0x04;
static const unsigned char OPERATION_DISCON_SOCKET = 0x08;
static const unsigned char OPERATION_CLOSE_SOCKET = 0x10;
static const unsigned char OPERATION_SEND_SOCKET = 0x20;
static const unsigned char OPERATION_SEND_MAC_SOCKET = 0x21;
static const unsigned char OPERATION_SEND_KEEP_SOCKET = 0x22;
static const unsigned char OPERATION_RECV_SOCKET = 0x40;


void sendCommand(unsigned char socket, unsigned char command);
void openSocket(unsigned char socket);

#ifdef	__cplusplus
}
#endif

#endif	/* MYW5500_H */
