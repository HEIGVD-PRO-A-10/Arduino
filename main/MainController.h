/**
 * File : MainController.h
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Main controller of Arduino Mega. Contains State Machine for program flow.
 *
 * Always call setup() method before usage
 * Call mss() in every loop.
 * A schéma of the MSS can be found in the doc
 */


#ifndef ARDUINO_MAINCONTROLLER_H
#define ARDUINO_MAINCONTROLLER_H

#include "../config/config.h"
#include "EspConnection.h"
#include "RFIDReader.h"
#include "LcdDisplayer.h"
#include "NumpadController.h"

#define MAX_UID_SIZE        10    // UID ne fera jamais plus que 10 bytes


class MainController {
public:
    /**
     * Default constructor. Init local vars.
     */
    MainController();

    /**
     * Calls setup on every module (RFID, NUMPAD, ESP Connection, LCD)
     */
    void setup();

    /**
     * Main State machine. Controls program flow.
     * @param nResetButton Reset Push Button for aborting user inputs such as Read amount, Read RFID card.
     */
    void mss(bool nResetButton);

private:

    RFIDReader rfidReader;
    EspConnection espConnection;
    LcdDisplayer lcdDisplayer;
    NumpadController nmpController;

    int     zx;                         // state machine: current state

    unsigned long timeoutStart;         // timeout for waiting on PIN

    byte    uId[MAX_UID_SIZE];          // RFID Card ID
    size_t  uIdSize;                    // RFID read ID Size

    size_t  pinLengthCounter;           // Counter for PIN input
    byte    pin[PIN_LENGTH];            // Pin

    bool    isDebit;                    // debit or credit flag

    byte    amountBuffer[3];            // Amount as array (debit or credit). One digit per Byte
    int     amountBufferCounter;        // Amount buffer counter index

    byte    amount;                     // Amount in one byte

};


#endif //ARDUINO_MAINCONTROLLER_H
