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
#include "../config/config.h"

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


byte WiFiCommunication::authenticate(String uid, String password){
    Serial.println("Entering func");
    HTTPClient http;
    http.begin("https://paybeer.artefactori.ch/api/login", this->ROOT_CA);
    http.addHeader("accept","application/json");
    http.addHeader("Content-Type", " application/x-www-form-urlencoded");
    int htCode = http.POST("tag_rfid=123456&pin_number=1241");
    String response = http.getString();
#ifndef nDebug
    Serial.print("Answer = ");
    Serial.println(response);

    Serial.println("Before http end");
    Serial.println("Finished func");
#endif

    if(htCode == 200){
        DeserializationError error = deserializeJson(jsonObject, response);
        if(error) return SERIALCODE_UNKOWN_ERROR;
        token = jsonObject["token"];
    }else if(htCode == 400){
        return SERIALCODE_LOGIN_WRONG_PARAM;
    }else if(htCode == 401){
        return SERIALCODE_LOGIN_WRONG_LOGIN;
    }else{
        return SERIALCODE_UNKOWN_ERROR;
    }
}