//
// Created by deni on 02/04/2020.
//

#ifndef TERMINAL_CONTROLLER_H
#define TERMINAL_CONTROLLER_H

#include "WiFiCommunication.h"

class Controller {
public:
    /**
     * Constructor of Controller object.
     */
    Controller();
    /**
     * Setup. Connects to WIFI
     */
    void setup();
    /**
     * Main process function. Must be called at each loop.
     */
    void process(unsigned char rxBytes[], int nbIncomingBytes);

    /**
     * get buffer Size
     */
    unsigned int getRxBufferSize();

private:
    /**
     * RX buffer size
     */
    const static unsigned int BUFFER_SIZE = 10;

    /**
     * Buffer of received bytes
     */
    unsigned char rxBuffer[BUFFER_SIZE];

    /**
     * index pointing to the last received byte in buffer.
     */
    unsigned int rxBuffer_index;


    /**
     * programm status
     */
    unsigned int zx;

    /**
     * Wifi Communication controller Object
     */
    WiFiCommunication wiFiCommunication;

    /**
     * commands
     */
    const static unsigned char NEW_PAYMENT = 0x10;
};


#endif //TERMINAL_CONTROLLER_H
