//
// Created by nico on 19.04.20.
//

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

    MainController();
    void setup();
    void mss();

private:

    RFIDReader rfidReader;
    EspConnection espConnection;
    LcdDisplayer lcdDisplayer;
    NumpadController nmpController;

    int     zx;

    unsigned long timeoutStart;

    byte    uId[MAX_UID_SIZE];
    size_t  uIdSize;

    size_t  pinLengthCounter;
    byte    pin[PIN_LENGTH];


};


#endif //ARDUINO_MAINCONTROLLER_H
