
#include "EspConnection.h"

EspConnection espConnection;
void setup() {
    delay(5000);
    Serial.begin(9600);
    espConnection.setup();
}

void loop() {
    Serial.println("send command!");
    espConnection.sendCmdToEsp(65);
    String jsonAnswer = espConnection.readAnswerFromEsp();
    Serial.println(jsonAnswer);
    delay(1000);
}


