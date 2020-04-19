//
// Created by deni on 26/03/2020.
//

#include "EspConnection.h"
#include <Arduino.h>

int EspConnection::hasAnswer() {
    return Serial2.available();
}

String EspConnection::readAnswerFromEsp(){
    String answer = Serial2.readString();
    return answer;
}


void EspConnection::sendCmdToEsp(unsigned char cmd){
    Serial2.write(cmd);
}

void EspConnection::setup() {
    Serial2.begin(9600);
}