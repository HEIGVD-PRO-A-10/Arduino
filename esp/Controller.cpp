//
// Created by deni on 02/04/2020.
//

#include "Controller.h"
#include "Base.h"
#include "../config/config.h"

#include <Arduino.h>
#include <base64.h>

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

    String generated_uid;
    String generated_pin;

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
            if(rxBuffer_index >= 9) zx = 102;
            break;

       case 102: // new Payment: invoke payment function
            byte result;
            generated_uid = generateUIDStringFromUID((const char*)(rxBuffer + 1));
            generated_pin = generatePINStringFromPIN((const char*)(rxBuffer + 5));
            result = wiFiCommunication.authenticate(generated_uid, generated_pin);
            writeByteOnSerial(result);
            zx = 500;
            break;

       case 500:
            rxBuffer_index = 0;
            zx = 0;
       break;
    }
}

void Controller::testPost() {

    writeOnSerial("Sending data...");

    String generated_uid = generateUIDStringFromUID("3456783e");
    String generated_pin = generatePINStringFromPIN("12345");

    byte answer = wiFiCommunication.authenticate(generated_uid, generated_pin);

    writeOnSerial(" -> Test Function result: ");
    writeByteOnSerial(answer);
}

String Controller::generateUIDStringFromUID(const char *uid) {

    String result = "";

    for (size_t i = 0; i < RFID_UID_SIZE; i++) {
        result += uid[i];
    }

    return base64::encode(result);
}

String Controller::generatePINStringFromPIN(const char *pin) {

    String result = "";

    for (size_t i = 0; i < PIN_LENGTH; i++) {
        result += pin[i];
    }

    return pin;
}