//
// Created by deni on 26/03/2020.
//

#include "EspConnection.h"
#include <Arduino.h>
String EspConnection::readAnswerFromEsp(){
    while(Serial2.available() <= 0);
    String answer = Serial2.readString();
    return answer;
}


void EspConnection::sendCmdToEsp(unsigned char cmd){
    Serial2.write(cmd);
}

void EspConnection::setup() {
    Serial2.begin(9600);
}