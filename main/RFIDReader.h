//
// Created by nico on 31.03.20.
//

#ifndef ARDUINO_RFIDREADER_H
#define ARDUINO_RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         45          // Configurable, see typical pin layout above
#define SS_PIN          44         // Configurable, see typical pin layout above

class RFIDReader {
private:

    MFRC522 mfrc522;

public:

    void setup();
    void read();
};

#endif //ARDUINO_RFIDREADER_H
