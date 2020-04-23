//
// Created by deni on 26/03/2020.
//

#ifndef TERMINAL_ESPCONNECTION_H
#define TERMINAL_ESPCONNECTION_H
#include <Arduino.h>

class EspConnection {
public:
    void setup();
    void sendCmdToEsp(unsigned char cmd);
    byte readAnswerFromEsp();
    bool hasAnswer();

private:
    char rxBuffer[256];
    unsigned int bufferPointer; // post increment
};


#endif //TERMINAL_ESPCONNECTION_H
