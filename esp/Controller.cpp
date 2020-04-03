//
// Created by deni on 02/04/2020.
//

#include "Controller.h"
#include "Base.h"
#include "JSONanswer.h"
#include <Arduino.h>

Controller::Controller() : rxBuffer_index(0), zx(0) {}

void Controller::setup() {
    bool wifiStatus = wiFiCommunication.connect();
    if(wifiStatus){
        writeOnSerial("{code:100}");
    }else{
        writeOnSerial("{code:999}");
        while(1);
    }
}

unsigned int Controller::getRxBufferSize(){
    return BUFFER_SIZE;
}

void Controller::process(unsigned char rxBytes[], int nbIncomingBytes) {
    // Copy bytes to rxBuffer
    for(int i = 0; i < nbIncomingBytes && i < BUFFER_SIZE; ++i){
        rxBuffer[++rxBuffer_index] = rxBytes[i];
    }
    
    switch (zx){
        case 0: // standby
            if(rxBytes != 0){
                if(rxBuffer[0] == NEW_PAYMENT) zx = 100; // new Payment
            }
            break;

        case 100: // new Payment: wait on full command
            if(rxBuffer_index <= 5) zx = 102;
            break;

       case 102: // new Payment: invoke payment function
            JSONanswer parser;
            writeOnSerial(parser.httpAnswerToJson(NEW_PAYMENT, wiFiCommunication.test()));
             //TODO invoke correct function. this is just a test
            zx = 500;
            break;

        case 500:
        rxBuffer_index = 0;
        zx = 0;
        break;


    }
}