#include "myw5500.h"
#include <xc.h>

void socketCommand(unsigned char socket, unsigned char command) {
    unsigned char blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x01));
    while(WriteSPI(blockSelect));

    while(WriteSPI(command));
    PORTAbits.RA5 = 1;
}

void openSocket(unsigned char socket) {
    socketCommand(socket, OPERATION_OPEN_SOCKET);
}

void send(unsigned char socket) {
    socketCommand(socket, OPERATION_SEND_SOCKET);
}

void receive(unsigned char socket) {
    socketCommand(socket, OPERATION_RECV_SOCKET);
}

void setSocketMode(unsigned char socket, unsigned char mode) {
    unsigned char blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x00));
    while(WriteSPI(blockSelect));

    while(WriteSPI(mode));
    PORTAbits.RA5 = 1;
}

void setSocketUDPMode(unsigned char socket) {
    setSocketMode(socket, SOCKET_UDP);
}

void setSocketSourcePort(unsigned char socket, unsigned short port) {
    unsigned char blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x04));
    while(WriteSPI(blockSelect));

    unsigned char highByte, lowByte;
    highByte = (port >> 8) & 0xFF;
    lowByte = port & 0xFF;

    while(WriteSPI(highByte));
    while(WriteSPI(lowByte));
    PORTAbits.RA5 = 1;
}
