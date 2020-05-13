/**
 * File : RFIDReader.h
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Controller for RFID reader module.
 * - Always call setup() function before usage.
 * - Once setup is done, you can call read() to know if a card is present or not.
 * - Once read() returned true, you can access to the ID of the card with getUIdBytes().
 *
 * Usage Example:
    RFIDReader rfidReader;
    rfidReader.setup();
    byte uId[MAX_UID_SIZE];

    if (rfidReader.read()) {

        rfidReader.printUid();
        size_t size = rfidReader.getUIdBytes(uId);

        Serial.print("Return Uid = ");
        for (size_t i = 0; i < size; i++) {
            Serial.print(uId[i], HEX);
        }

        Serial.println("");

    }
*/

#ifndef ARDUINO_RFIDREADER_H
#define ARDUINO_RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         45          // Pin utilisée sur le méga
#define SS_PIN          44          // Pin utilisée sur le méga

class RFIDReader {
private:

    MFRC522 mfrc522;

public:

    /**
     * Initialise the reader
     */
    void setup();

    /**
     * Checks if a card is available.
     *
     * @return true if card has been read. Else false.
     */
    bool read();

    /**
     * print on serial the read UID. Only used for debuging
     */
    void printUid();

    /**
     * Last UId that was read by de module.
     *
     * @param array (In Out) that will be filled with the UID
     *
     * @return returns the length of the UID.
     */
    size_t getUIdBytes(byte *array);
};

#endif //ARDUINO_RFIDREADER_H
