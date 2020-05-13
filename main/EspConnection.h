/**
 * File : EspConnection.h
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Class used for communication with ESP32. Connection is made over UART Serial2 interface.
 */

#ifndef TERMINAL_ESPCONNECTION_H
#define TERMINAL_ESPCONNECTION_H
#include <Arduino.h>

class EspConnection {
public:
    /**
     * Setup Serial2 interface
     */
    void setup();

    /**
     * Send raw byte to ESP32
     * @param cmd byte to send
     */
    void sendCmdToEsp(byte cmd);

    /**
     * Read next byte in RX buffer
     * @return received byte from ESP
     */
    byte readAnswerFromEsp();

    /**
     * Returns if byte is received
     * @return true if at least 1 byte is in RX buffer
     */
    bool hasAnswer();

private:
    char rxBuffer[256];                 // received bytes buffer
    unsigned int bufferPointer;         // rx buffer index, post increment
};


#endif //TERMINAL_ESPCONNECTION_H
