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
    WiFi.begin(this->SSID, this->PASSWORD);
    for(int i = 0; i < this->CONNECT_TIMEOUT; ++i){
        if(WiFi.status() == WL_CONNECTED){
            this->connected = true;
            return true;
        }
        delay(500);
    }
    return false;
}

bool WiFiCommunication::isConnected() {
    return this->isConnected();
}

HTTPAnswer WiFiCommunication::test() {
    HTTPClient http;
    http.begin("https://entojwjv9t8k.x.pipedream.net", this->ROOT_CA);
    http.addHeader("api_token",  "yooowhatuppp");
    int htCode = http.GET();
    HTTPAnswer httpAnswer(htCode, http.getString());
    http.end();
    return httpAnswer;
}

HTTPAnswer WiFiCommunication::authenticate(String uid, String password){
    HTTPClient http;
    http.begin("https://entojwjv9t8k.x.pipedream.net", this->ROOT_CA);
    http.addHeader("api_token",  "yooowhatuppp");
    int htCode = http.POST("Hello World:RQUEST");
    HTTPAnswer httpAnswer(htCode, http.getString());
    http.end();
    return httpAnswer;
}