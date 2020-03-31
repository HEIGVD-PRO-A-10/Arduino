//
// Created by nico on 31.03.20.
//

#include "RFIDReader.h"


void RFIDReader::setup() {

    mfrc522 = MFRC522(SS_PIN, RST_PIN);

    SPI.begin();
    mfrc522.PCD_Init();
    delay(4);				// On peut avoir des soucis sans le délai
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}

void RFIDReader::read() {

    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
