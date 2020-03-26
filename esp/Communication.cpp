//
// Created by deni on 26/03/2020.
//

#include "Communication.h"
#include "HTTPAnswer.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

bool Communication::connect() {
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

bool Communication::isConnected() {
    return this->isConnected();
}

HTTPAnswer Communication::test() {
    HTTPClient http;
    http.begin("https://en68kwqq65f2.x.pipedream.net/", this->root_ca);
    http.addHeader("api_token",  "yooowhatuppp");
    int htCode = http.GET();
    HTTPAnswer httpAnswer(htCode, http.getString());
    http.end();
    return httpAnswer;
}