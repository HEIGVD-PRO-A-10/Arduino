//
// Created by deni on 02/04/2020.
//

#include "WiFiCommunication.h"
#include "HTTPAnswer.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

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
    http.begin("https://en68kwqq65f2.x.pipedream.net/", this->ROOT_CA);
    http.addHeader("api_token",  "yooowhatuppp");
    int htCode = http.GET();
    HTTPAnswer httpAnswer(htCode, http.getString());
    http.end();
    return httpAnswer;
}