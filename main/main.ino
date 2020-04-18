#include "EspConnection.h"
#include "RFIDReader.h"
#include "LcdDisplayer.h"
#include "NumpadController.h"

RFIDReader rfidReader;
EspConnection espConnection;
LcdDisplayer lcdDisplayer;

#define MAX_UID_SIZE 10    // UID ne fera jamais plus que 10 bytes

void testNumPadMSS();

void setup() {

    delay(5000);

    Serial.begin(9600);		// Init du serial
    while (!Serial);		// Attends que le serial soit lu

//    // Setup des différents modules
    rfidReader.setup();
//    espConnection.setup();
    lcdDisplayer.setup();
    lcdDisplayer.displayString("Scan a card...");

}

void loop() {

    // Exemple RFID & Affichage écran
/*
    byte uId[MAX_UID_SIZE];

    if (rfidReader.read()) {

        // rfidReader.printUid();
        size_t size = rfidReader.getUIdBytes(uId);

//        Serial.print("Return Uid = ");
//        for (size_t i = 0; i < size; i++) {
//            Serial.print(uId[i], HEX);
//        }
        lcdDisplayer.clearDisplay();
        lcdDisplayer.setCursor(0, 0);
        lcdDisplayer.displayString("New card !");

        // Nouvelle ligne
        lcdDisplayer.setCursor(1, 0);
        lcdDisplayer.displayString("No: ");

        for (size_t i = 0; i < size; i++) {
            lcdDisplayer.displayByte(uId[i]);
        }
    }

    // Exemple ESP

    //espConnection.sendCmdToEsp(65);
    //String jsonAnswer = espConnection.readAnswerFromEsp();
    //Serial.println(jsonAnswer);
    //delay(1000);
    */
    testNumPadMSS();
}


//TEST MSS
NumpadController nmpController;

void testNumPadMSS() {

    nmpController.mss();

    if (nmpController.readDone()) {

        Serial.print("Numpad Value: ");
        Serial.println(nmpController.value());
        nmpController.read();
    }
}
