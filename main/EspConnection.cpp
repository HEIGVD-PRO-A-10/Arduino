//
// Created by deni on 26/03/2020.
//

#include "EspConnection.h"
#include <Arduino.h>

bool EspConnection::hasAnswer() {
    return Serial2.available();
    int bytesToReadCount = Serial2.available();
    bool gotEndOfLine = false;
    if(bytesToReadCount){
        for(int i = 0; i < bytesToReadCount; ++i){
            rxBuffer[bufferPointer] = Serial2.read();
            ++bufferPointer;
        }
        gotEndOfLine = rxBuffer[bufferPointer - 1] == '\n';
    }
    return gotEndOfLine;
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