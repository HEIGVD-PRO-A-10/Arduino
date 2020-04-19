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
    String readAnswerFromEsp();
    int hasAnswer();
};


#endif //TERMINAL_ESPCONNECTION_H
