//
// Created by nico on 31.03.20.
//

#include <Arduino.h>

#include "RFIDReader.h"


void RFIDReader::setup() {

    mfrc522 = MFRC522(SS_PIN, RST_PIN);

    SPI.begin();
    mfrc522.PCD_Init();
    delay(4);				// On peut avoir des soucis sans le délai
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println(F("RFIDReader init done. Scan a tag to get its UID..."));

}

bool RFIDReader::read() {

    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return false;
    }

    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return false;
    }

    return true;
}

void RFIDReader::printUid() {

    Serial.print("Reader Uid = ");

    for (size_t i = 0; i < size_t(mfrc522.uid.size); i++) {
        if (i != 0) {
            Serial.print(", ");
        }
        Serial.print("0x");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.println("");

}

size_t RFIDReader::getUIdBytes(byte *array) {

    size_t i;

    for (i = 0; i < size_t(mfrc522.uid.size); i++) {
        array[i] = mfrc522.uid.uidByte[i];
    }

    return i;

}