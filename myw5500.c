#include "myw5500.h"
#include <xc.h>


void socketCommand(uint8_t socket, uint8_t command) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x01));
    while(WriteSPI(blockSelect));

    while(WriteSPI(command));
    PORTAbits.RA5 = 1;
}

void openSocket(uint8_t socket) {
    socketCommand(socket, OPERATION_OPEN_SOCKET);
}

void closeSocket(uint8_t socket) {
    socketCommand(socket, OPERATION_CLOSE_SOCKET);
}

void send(uint8_t socket) {
    socketCommand(socket, OPERATION_SEND_SOCKET);
}

void receive(uint8_t socket) {
    socketCommand(socket, OPERATION_RECV_SOCKET);
}

void setSocketMode(uint8_t socket, uint8_t mode) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x00));
    while(WriteSPI(blockSelect));

    while(WriteSPI(mode));
    PORTAbits.RA5 = 1;
}

void setSocketUDPMode(uint8_t socket) {
    setSocketMode(socket, SOCKET_UDP);
}

void setSocketSourcePort(uint8_t socket, uint16_t port) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x04));
    while(WriteSPI(blockSelect));

    uint8_t highByte, lowByte;
    highByte = (port >> 8) & 0xFF;
    lowByte = port & 0xFF;

    while(WriteSPI(highByte));
    while(WriteSPI(lowByte));
    PORTAbits.RA5 = 1;
}

void setSocketDestinationPort(uint8_t socket, uint16_t port) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x10));
    while(WriteSPI(blockSelect));

    uint8_t highByte, lowByte;
    highByte = (port >> 8) & 0xFF;
    lowByte = port & 0xFF;

    while(WriteSPI(highByte));
    while(WriteSPI(lowByte));
    PORTAbits.RA5 = 1;
}

void setSocketDestinationIPAddress(uint8_t socket, uint8_t *address) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x0C));
    while(WriteSPI(blockSelect));

    while(WriteSPI(address[0]));
    while(WriteSPI(address[1]));
    while(WriteSPI(address[2]));
    while(WriteSPI(address[3]));
    PORTAbits.RA5 = 1;
}

uint8_t readSocketStatus(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x03));
    while(WriteSPI(blockSelect));

    uint8_t status = ReadSPI();
    PORTAbits.RA5 = 1;

    return status;
}

uint16_t readWritePointer(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x24));
    while(WriteSPI(blockSelect));

    uint8_t writePointerByte1, writePointerByte2;
    writePointerByte1 = ReadSPI();
    writePointerByte2 = ReadSPI();
    PORTAbits.RA5 = 1;

    uint16_t writePointer = (writePointerByte1 << 8) + writePointerByte2;
    return writePointer;
}

void increaseWritePointer(uint8_t socket, uint16_t len) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x24));
    while(WriteSPI(blockSelect));

    while(WriteSPI((len >> 8) & 0xFF));
    while(WriteSPI(len & 0xFF));
    PORTAbits.RA5 = 1;
}

void writeToSocketTxBuffer(uint8_t socketTxBuffer, uint16_t writePointer, unsigned char *data) {
    uint8_t blockSelect = (socketTxBuffer << 3) + 0x04;

    uint8_t writePointerH, writePointerL;
    writePointerH = (writePointer >> 8) & 0xFF;
    writePointerL = writePointer & 0xFF;

    PORTAbits.RA5 = 0;
    while(WriteSPI(writePointerH));
    while(WriteSPI(writePointerL));
    while(WriteSPI(blockSelect)); //socket 1 tx buffer

    for (uint16_t i=0; i<sizeof(data); i++) {
       while(WriteSPI(data[i]));
    }
    PORTAbits.RA5 = 1;
}