//
// Created by deni on 02/04/2020.
//

#include "WiFiCommunication.h"
#include "HTTPAnswer.h"
#include "Base.h"
#include "../config/config.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <HTTPClient.h>

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


byte WiFiCommunication::authenticate(String uid, String password) {

    HTTPClient http;
//    http.begin("https://paybeer.artefactori.ch/api/login?tag_rfid=123456&pin_number=12345", this->ROOT_CA);
    http.begin("http://192.168.1.102:8000/api/login");
    http.addHeader("accept","application/json");
    http.addHeader("Content-Type", " application/x-www-form-urlencoded");

    int htCode;
    htCode = http.POST("tag_rfid=319765&pin_number=62377");
    String response = http.getString();

    http.end();

#ifndef nDebug
    writeOnSerial("Answer = ");
    writeOnSerial(response);

    writeOnSerial("HtCode = ");
    writeIntOnSerial(htCode);
#endif

    if (htCode == 200) {

        DeserializationError error = deserializeJson(jsonObject, response);

        if (error) {
            return SERIALCODE_UNKOWN_ERROR;
        }

        token = jsonObject["token"];

#ifndef nDebug
        writeOnSerial("Token set to:");
        writeOnSerial(token);
#endif
        return SERIALCODE_LOGIN_OK;
    }
    else if (htCode == 400) {
        return SERIALCODE_LOGIN_WRONG_PARAM;
    }
    else if (htCode == 401) {
        return SERIALCODE_LOGIN_WRONG_LOGIN;
    }
    else {
        return SERIALCODE_UNKOWN_ERROR;
    }
}