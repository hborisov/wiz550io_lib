#include "myw5500.h"
#include <xc.h>
#include "plib/usart.h"
#include <string.h>


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

void connect(uint8_t socket) {
    socketCommand(socket, OPERATION_CONNECT_SOCKET);
}

void disconnect(uint8_t socket) {
    socketCommand(socket, OPERATION_DISCON_SOCKET);
}

void close(uint8_t socket) {
    socketCommand(socket, OPERATION_CLOSE_SOCKET);
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

void setSocketTCPMode(uint8_t socket) {
    setSocketMode(socket, SOCKET_TCP);
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

uint8_t readSocketInterruptRegister(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x02));
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

uint16_t readReadPointer(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x28));
    while(WriteSPI(blockSelect));

    uint8_t readBuffPointer1 = ReadSPI();
    uint8_t readBuffPointer2 = ReadSPI();
    PORTAbits.RA5 = 1;

    uint16_t readPointer = (readBuffPointer1 << 8) + readBuffPointer2;
    return readPointer;
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

void increaseReadPointer(uint8_t socket, uint16_t len) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x28));
    while(WriteSPI(blockSelect));

    while(WriteSPI((len >> 8) & 0xFF));
    while(WriteSPI(len & 0xFF));
    PORTAbits.RA5 = 1;
}

void writeToSocketTxBuffer(uint8_t socketTxBuffer, uint16_t writePointer, unsigned char* data) {
    uint8_t blockSelect = (socketTxBuffer << 3) + 0x04;

    uint8_t writePointerH, writePointerL;
    writePointerH = (writePointer >> 8) & 0xFF;
    writePointerL = writePointer & 0xFF;

    PORTAbits.RA5 = 0;
    while(WriteSPI(writePointerH));
    while(WriteSPI(writePointerL));
    while(WriteSPI(blockSelect));

    uint16_t len = strlen(data);
    for (uint16_t i=0; i<len; i++) {
       while(WriteSPI(data[i]));
    }
    PORTAbits.RA5 = 1;
}

uint16_t readFromSocketRxBuffer(uint8_t socketRxBuffer, uint16_t readPointer, unsigned char *buffer) {
    uint8_t blockSelect = (socketRxBuffer << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI((readPointer >> 8) & 0xFF));
    while(WriteSPI(readPointer & 0xFF));
    while(WriteSPI(blockSelect));

    for (int i=0; i<UDP_HEADER_LENGTH; i++) {
        unsigned char temp = ReadSPI();
            //while(BusyUSART());
            //WriteUSART(temp);
            buffer[i] = temp;
    }
    PORTAbits.RA5 = 1;
    uint16_t dataLength = (buffer[6] << 8) + buffer[7];

    PORTAbits.RA5 = 0;
    uint16_t dataPointer = readPointer + UDP_HEADER_LENGTH;
    while(WriteSPI((dataPointer >> 8) & 0xFF));
    while(WriteSPI(dataPointer & 0xFF));
    while(WriteSPI(blockSelect));

    for (int j=0; j<dataLength; j++) {
        buffer[j+8] = ReadSPI();
            //while(BusyUSART());
            //WriteUSART(buffer[j+8]);
    }
    PORTAbits.RA5 = 1;

    return dataLength;
}

void readFromSocketRxBufferLen(uint8_t socketRxBuffer, uint16_t readPointer, unsigned char *buffer, uint16_t len) {
    uint8_t blockSelect = (socketRxBuffer << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI((readPointer >> 8) & 0xFF));
    while(WriteSPI(readPointer & 0xFF));
    while(WriteSPI(blockSelect));

    for(int i=0; i<len; i++) {
        buffer[i] = ReadSPI();
    }

    PORTAbits.RA5 = 1;
}

uint16_t readNumberOfBytesReceived(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);
    
    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x26));
    while(WriteSPI(blockSelect));  //read number of bytes read

    uint8_t numBytesRead1 = ReadSPI();
    uint8_t numBytesRead2 = ReadSPI();
    PORTAbits.RA5 = 1;

    uint16_t numBytesRead = (numBytesRead1 << 8) + numBytesRead2;
    return numBytesRead;
}

void clearInterrupts(uint8_t socket) {
    uint8_t blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x02));
    while(WriteSPI(blockSelect));  //read number of bytes read

    while(WriteSPI(0xFF));
    PORTAbits.RA5 = 1;
}

uint16_t readTxFreeSize(uint8_t socket) {
    uint8_t blockSelect = (socket << 3);

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x20));
    while(WriteSPI(blockSelect));  //read number of bytes read

    uint8_t freeSizeHighByte = ReadSPI();
    uint8_t freeSizeLowByte = ReadSPI();
    PORTAbits.RA5 = 1;

    uint16_t freeTxSize = (freeSizeHighByte << 8) + freeSizeLowByte;
    return freeTxSize;
}