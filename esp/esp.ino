#include <Arduino.h>


#include "Communication.h"
#include "HTTPAnswer.h"
#include "JSONanswer.h"
void processCMD(unsigned char cmd);

Communication communication;
int incomingByte = 0;
void setup(void){
    pinMode(2,OUTPUT);
	Serial.begin(9600);
    digitalWrite(2,HIGH);
	delay(5000);
    digitalWrite(2,LOW);
    bool wifiStatus = communication.connect();
    if(wifiStatus){
        Serial.println("{code:100}");
    }else{
        Serial.println("{code:999}");
        while(1);
    }

}

void loop(void){
    if (Serial.available() > 0) {
        digitalWrite(2,HIGH);
        delay(500);
        incomingByte = Serial.read();
        processCMD((unsigned char)incomingByte);
    }
}

void processCMD(unsigned char cmd){
    JSONanswer parser;
    switch (cmd){
        case 65:
            digitalWrite(2,LOW);
            String json = parser.httpAnswerToJson(cmd, communication.test());
            Serial.println(json);
            break;
    }
}
