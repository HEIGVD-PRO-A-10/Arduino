//
// Created by deni on 02/04/2020.
//

#ifndef TERMINAL_CONTROLLER_H
#define TERMINAL_CONTROLLER_H

#include "WiFiCommunication.h"
/**
 * Controller class:
 * The controller class is the main brain of the ESP module.
 *
 * The object controls the flow between the incoming Serial line from the Aruino Mega, invokes the http request and
 * responds to the Mega over Serial again.
 *
 * MSS:
 * It contains a sort of State Machine. Used for not stopping
 * the main loop of the system.
 * The process function should be called at each loop of the system and passing the new bytes (if available) read on
 * the incoming serial line.
 * The object contains a ZX value which indicates the actual State of the MSS.
 *
 *
 */
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

    void testPost();

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

};


#endif //TERMINAL_CONTROLLER_H
