//
// Created by deni on 02/04/2020.
//

#include "Controller.h"
#include "Base.h"
#include "../config/config.h"

#include <Arduino.h>

Controller::Controller() : rxBuffer_index(0), zx(0) {}

void Controller::setup() {
    // init Wifi
    bool wifiStatus = wiFiCommunication.connect();

    if(wifiStatus){
        Serial.write(SERIALCODE_WIFI_OK);
    }else{
        Serial.write(SERIALCODE_NO_WIFI);
        // Stop here if wifi is not working
        while(1);
    }
}

unsigned int Controller::getRxBufferSize(){
    return BUFFER_SIZE;
}

/**
 * This function behaves different according to the ZX state. The purpose of every State is in the documentation.
 *
 *
 * @param rxBytes Bytes read on the incoming serial line from the Arduino mega
 * @param nbIncomingBytes number of bytes read.
 */
void Controller::process(byte rxBytes[], int nbIncomingBytes) {
    // Copy bytes to rxBuffer
    for(int i = 0; i < nbIncomingBytes && i < BUFFER_SIZE; ++i){
        rxBuffer[++rxBuffer_index] = rxBytes[i];
    }

    // STATE MACHINE
    switch (zx){
        case 0: // standby
            if(rxBytes != 0){
                if(rxBuffer[0] == SERIALCOMMAND_BARMAN_AUTHENTICATION)
                    zx = 100; // new Payment
                else if(rxBuffer[0] == SERIALCOMMAND_PAYMENT) zx = 0; //TODO
                else if(rxBuffer[0] == SERIALCOMMAND_NEW_CARD) zx = 0; //TODO
                else if(rxBuffer[0] == SERIALCOMMAND_RECHARGE) zx = 0; //TODO
            }
            break;

        case 100: // new Payment: wait on full command
            if(rxBuffer_index <= 9) zx = 102;
            break;

       case 102: // new Payment: invoke payment function
            byte result;
            result = wiFiCommunication.authenticate((const char*)(rxBuffer + 1), (const char*)(rxBuffer + 5));
            Serial.write(result);
            zx = 500;
            break;

       case 500:
            rxBuffer_index = 0;
            zx = 0;
       break;
    }
}

void Controller::testPost() {

    Serial.print("Sending data...");

    byte answer = wiFiCommunication.authenticate("yoo","juu");

    delay(1000);
    Serial.print(" -> Test Function result: ");
    Serial.println(answer);
}