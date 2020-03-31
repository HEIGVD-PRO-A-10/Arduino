#include "EspConnection.h"
#include "RFIDReader.h"

RFIDReader rfidReader;
EspConnection espConnection;

#define MAX_UID_SIZE 10    // UID ne fera jamais plus que 10 bytes

void setup() {

    delay(5000);

    Serial.begin(9600);		// Initialize serial communications with the PC
    while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

    // Setup des différents modules
    rfidReader.setup();
    espConnection.setup();
}

void loop() {

    // Exemple RFID

    byte uId[MAX_UID_SIZE];

    if (rfidReader.read()) {

        rfidReader.printUid();
        size_t size = rfidReader.getUIdBytes(uId);

        Serial.print("Return Uid = ");
        for (size_t i = 0; i < size; i++) {
            Serial.print(uId[i], HEX);
        }

        Serial.println("");

    }

    // Exemple ESP

    //espConnection.sendCmdToEsp(65);
    //String jsonAnswer = espConnection.readAnswerFromEsp();
    //Serial.println(jsonAnswer);
    //delay(1000);
}
