#include "myw5500.h"
#include <xc.h>

void sendCommand(unsigned char socket, unsigned char command) {
    unsigned char blockSelect = (socket << 3) + 0x04;

    PORTAbits.RA5 = 0;
    while(WriteSPI(0x00));
    while(WriteSPI(0x01));
    while(WriteSPI(blockSelect));

    while(WriteSPI(command));
    PORTAbits.RA5 = 1;
}

void openSocket(unsigned char socket) {
    sendCommand(socket, OPERATION_OPEN_SOCKET);
}
