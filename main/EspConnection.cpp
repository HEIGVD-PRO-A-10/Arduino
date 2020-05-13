/**
 * File : EspConnection.cpp
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Implementation of EspConnection Object.
 */

#include "EspConnection.h"
#include <Arduino.h>

void EspConnection::setup() {
    Serial2.begin(9600);
}

bool EspConnection::hasAnswer() {
    return Serial2.available();
}

byte EspConnection::readAnswerFromEsp(){
    return Serial2.read();
}

void EspConnection::sendCmdToEsp(byte cmd){
    Serial2.write(cmd);
}

