/*
#include "EspConnection.h"
#include "RFIDReader.h"

EspConnection espConnection;
RFIDReader rfidReader;

void setup() {
    delay(5000);
    Serial.begin(9600);
    while(!Serial);
    rfidReader.setup();
    //espConnection.setup();

}

void loop() {



    //Serial.println("send command!");
    //espConnection.sendCmdToEsp(65);
    //String jsonAnswer = espConnection.readAnswerFromEsp();
    //Serial.println(jsonAnswer);
    //delay(1000);
}

*/

#include "RFIDReader.h"

RFIDReader rfidReader;

void setup() {

    Serial.begin(9600);		// Initialize serial communications with the PC
    while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    rfidReader.setup();
}

void loop() {
    rfidReader.read();
}
