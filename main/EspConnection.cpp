//
// Created by deni on 26/03/2020.
//

#include "EspConnection.h"
#include <Arduino.h>

bool EspConnection::hasAnswer() {
    return Serial2.available();
}

byte EspConnection::readAnswerFromEsp(){
    return Serial2.read();
}


void EspConnection::sendCmdToEsp(byte cmd){
    Serial2.write(cmd);
}

void EspConnection::setup() {
    Serial2.begin(9600);
}