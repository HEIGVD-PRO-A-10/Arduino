//
// Created by deni on 02/04/2020.
//

#include "WiFiCommunication.h"
#include "HTTPAnswer.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>


bool WiFiCommunication::connect() {

    WiFi.disconnect();
    delay(1);
    WiFi.begin(this->SSID, this->PASSWORD);

    for(int i = 0; i < this->CONNECT_TIMEOUT; ++i){
        Serial.println(WiFi.status());
        if(WiFi.status() == WL_CONNECTED){
            this->connected = true;
            return true;
        }
        delay(1000);
    }
    return false;
}

bool WiFiCommunication::isConnected() {
    return this->isConnected();
}

HTTPAnswer WiFiCommunication::test() {
    HTTPClient http;
    http.begin("https://enqidtc71xg9g.x.pipedream.net/", this->ROOT_CA);
    http.addHeader("api_token",  "yooowhatuppp");
    int htCode = http.GET();
    HTTPAnswer httpAnswer(htCode, http.getString());
    http.end();
    return httpAnswer;
}

HTTPAnswer WiFiCommunication::authenticate(String uid, String password){
    Serial.println("Entering func");
    HTTPClient http;
    http.begin("https://paybeer.artefactori.ch/api/login", this->ROOT_CA);
    http.addHeader("accept:","application/json");
    http.addHeader("Content-Type:", " application/x-www-form-urlencoded");
    int htCode = http.POST("tag_rfid=12345&pin_number=1234");
    Serial.print("Answer = ");
    Serial.println(http.getString());
    HTTPAnswer httpAnswer(htCode, http.getString());
    Serial.println("Before http end");
    http.end();
    Serial.println("Finished func");
    return httpAnswer;
}