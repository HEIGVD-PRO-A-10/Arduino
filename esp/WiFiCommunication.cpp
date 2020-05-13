//
// Created by deni on 02/04/2020.
//

#include "WiFiCommunication.h"
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

    for(int i = 0; i < this->CONNECT_TIMEOUT; ++i) {

#ifndef nDebug
        Serial.println(WiFi.status());
#endif
        if(WiFi.status() == WL_CONNECTED){
            return true;
        }
        delay(1000);
    }
    return false;
}

bool WiFiCommunication::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

byte WiFiCommunication::newUser(String uid) {
    HTTPClient http;
    http.begin(SERVER + "/api/new-user"); //, this->ROOT_CA);
    http.addHeader("accept","application/json");
    http.addHeader("Authorization",  String("Bearer ") + token);
    http.addHeader("Content-Type", " application/x-www-form-urlencoded");

    int htCode;
    String payload = "tag_rfid=" + uid;

    htCode = http.POST(payload);
    String response = http.getString();
    http.end();

    switch (htCode){
        case 201:
            return SERIALCODE_NEWUSER_OK;
        case 400:
            return SERIALCODE_NEWUSER_ERROR;
        case 401:
            return SERIALCODE_TOKEN_NOT_VALID;
    }
    return SERIALCODE_UNKOWN_ERROR;
}

byte WiFiCommunication::transaction(String uid, String amount) {
    HTTPClient http;
    http.begin(SERVER + "/api/transaction"); //, this->ROOT_CA);
    http.addHeader("accept","application/json");
    http.addHeader("Authorization",  String("Bearer ") + token);
    http.addHeader("Content-Type", " application/x-www-form-urlencoded");

    int htCode;
    String payload = "tag_rfid=" + uid + "&amount=" + amount + "&num_terminal=1";

    htCode = http.POST(payload);
    String response = http.getString();
    http.end();

    switch (htCode){
        case 201:
            return SERIALCODE_TRANSACTION_OK;
        case 451:
            return SERIALCODE_TRANSACTION_NOT_ENOUGH_CREDIT;
        case 450:
            return SERIALCODE_TRANSACTION_NOT_VALID_CARD;
        case 401:
            return SERIALCODE_TOKEN_NOT_VALID;
    }
    return SERIALCODE_UNKOWN_ERROR;
}

byte WiFiCommunication::authenticate(String uid, String password) {

    HTTPClient http;
    http.begin(SERVER + "/api/login"); //, this->ROOT_CA);
    http.addHeader("accept","application/json");
    http.addHeader("Content-Type", " application/x-www-form-urlencoded");

    int htCode;
    String payload = "tag_rfid=" + uid + "&pin_number=" + password;

    htCode = http.POST(payload);
    String response = http.getString();

    http.end();

    //TODO SWITCH CASE
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