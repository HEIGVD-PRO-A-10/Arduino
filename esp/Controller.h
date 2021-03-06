/**
 * File : Controller.h
 * Project : PayBeer Terminal (Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
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
 */


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
     *
     * @return true if setup was ok, returns false sinon
     */
    bool setup();
    /**
     * Main process function. Must be called at each loop.
     */
    void process(byte rxBytes[], int nbIncomingBytes);

    /**
     * get buffer Size
     */
    unsigned int getRxBufferSize();

    /**
     * Questening the current wifi status
     * @return true if wifi connected.
     */
    bool wifiConnected();

private:
    /**
     * Helper function for converting String from UID array
     * @param uid array containing UID
     * @return Same in String
     */
    String generateUIDStringFromUID(const char* uid);

    /**
     * Helper function for converting String from pin array
     * @param uid array containing pin
     * @return Same in String
     */
    String generatePINStringFromPIN(const char* pin);

    /**
     * RX buffer size
     */
    const static unsigned int BUFFER_SIZE = 32;

    /**
     * Buffer of received bytes
     */
    byte rxBuffer[BUFFER_SIZE];

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
