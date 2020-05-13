/**
 * File : Controller.cpp
 * Project : PayBeer Terminal (Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Implementation of Controller class.
 */


#include "Controller.h"
#include "Base.h"
#include "../config/config.h"

#include <Arduino.h>
#include <base64.h>

Controller::Controller() : rxBuffer_index(0), zx(0) {}

bool Controller::setup() {
    // init Wifi
    bool wifiStatus = wiFiCommunication.connect();

    if(wifiStatus){
        return true;
    }else{
        return false;
    }
}

bool Controller::wifiConnected(){
    return wiFiCommunication.isConnected();
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
    byte result;
    String generated_uid;
    String generated_pin;


    // Copy bytes to rxBuffer
    for(int i = 0; i < nbIncomingBytes && i < BUFFER_SIZE; ++i){
        rxBuffer[rxBuffer_index++] = rxBytes[i];
    }

    // STATE MACHINE
    switch (zx){
        case 0: // standby
            if(rxBuffer_index != 0){
                if(rxBuffer[0] == SERIALCOMMAND_BARMAN_AUTHENTICATION)
                    zx = 100;
                else if(rxBuffer[0] == SERIALCOMMAND_TRANSACTION)
                    zx = 200;
                else if(rxBuffer[0] == SERIALCOMMAND_NEW_USER)
                    zx = 300;
                else{
                    rxBuffer_index = 0;
                }
            }
            break;

        case 100: // new authentication: wait on full command
            if(rxBuffer_index >= ESP32_CMD_LENGTH + RFID_UID_SIZE + PIN_LENGTH) zx = 102;
            break;

        case 102: // new authentication: invoke authentication function
            generated_uid = generateUIDStringFromUID((const char*)(rxBuffer + 1));
            generated_pin = generatePINStringFromPIN((const char*)(rxBuffer + 5));
            result = wiFiCommunication.authenticate(generated_uid, generated_pin);
            writeByteOnSerial(result);
            zx = 500;
            break;

        case 200:
            if(rxBuffer_index >= ESP32_CMD_LENGTH + RFID_UID_SIZE + ESP32_AMOUNT_LENGTH) zx = 202;
            break;

        case 202:
            generated_uid = generateUIDStringFromUID((const char*)(rxBuffer + 1));
            result = wiFiCommunication.transaction(generated_uid, String( (*(rxBuffer + 5) > 127) ? *(rxBuffer + 5) - 256 : *(rxBuffer + 5)  ) );
            writeByteOnSerial(result);
            zx = 500;
            break;

        case 300:
            if(rxBuffer_index >= ESP32_CMD_LENGTH + RFID_UID_SIZE) zx = 302;
            break;

        case 302:
            generated_uid = generateUIDStringFromUID((const char*)(rxBuffer + 1));
            result = wiFiCommunication.newUser(generated_uid);
            writeByteOnSerial(result);
            zx = 500;
            break;

        case 500:
            rxBuffer_index = 0;
            zx = 0;
        break;
    }
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

