/**
 * File : MainController.cpp
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Implementation of MainController class.
 *
 */

#include <Arduino.h>

#include "MainController.h"

#define TIMEOUT_PIN_DELTA       30 * 1000
#define HEX_TO_DECIMAL_OFFSET   0x30
#define MAX_DIGITS_AMOUNT       3

MainController::MainController() : zx(0),
                                   uIdSize(0),
                                   pinLengthCounter(0)
{}

void MainController::setup() {

    Serial.println("Setting up modules...");

    /* RFID */
    rfidReader.setup();
    Serial.println("RFID Reader OK.");

    /* ESP Serial Connection */
    espConnection.setup();
    Serial.println("ESP32 OK.");

    /* Numpad */
    nmpController.setup();
    Serial.println("NUMPAD OK.");

    /* LCD Display */
    lcdDisplayer.setup();
    Serial.println("LCD OK.");
    lcdDisplayer.clearDisplay();
    lcdDisplayer.displayString("Wait on WiFi");

    Serial.println("Init Done.");

}

void MainController::mss(bool resetButton) {

    switch (zx) {

        // Init
        case 0:

            if (espConnection.hasAnswer()) {

                byte answer = espConnection.readAnswerFromEsp();

                #ifndef nDebug
                Serial.print("zx = 0; Got answer: 0x");
                Serial.println(answer, HEX);
                #endif

                if (answer == SERIALCODE_WIFI_OK) {

                    zx = 10;
                    lcdDisplayer.displayString("Scan admin card");
                }
                else {

                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("No connection...");
                    lcdDisplayer.setCursor(1, 0);
                    lcdDisplayer.displayString("Reset Arduino");

                    zx = 400;
                }
            }
            break;

        // Wait for Barman card
        case 10:

            if (rfidReader.read()) {

                #ifndef nDebug
                Serial.print("zx = 10; Scanned a card:");
                for (size_t i = 0; i < RFID_UID_SIZE; i++) {
                    Serial.print(uId[i], HEX);
                }
                Serial.println("");
                #endif

                uIdSize = rfidReader.getUIdBytes(uId);

                if (uIdSize != RFID_UID_SIZE) {

                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Invalid UID...");
                    return;
                }

                pinLengthCounter = 0;

                lcdDisplayer.clearDisplay();
                lcdDisplayer.displayString("Enter PIN code");
                lcdDisplayer.setCursor(1, 0);

                timeoutStart = millis();
                zx = 20;

            }
            break;

        // Start Read
        case 20:

            nmpController.read();
            zx = 30;

            #ifndef nDebug
            Serial.println("zx = 20; Enabled Read");
            #endif

            break;

        // Read pin
        case 30:

            nmpController.mss();

            if (nmpController.readDone()) {

                byte value = nmpController.value();

                #ifndef nDebug
                Serial.print("zx = 30; Read value: 0x");
                Serial.println(value, HEX);
                #endif
                if (value == (byte) 0xC) {

                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Enter PIN code");
                    lcdDisplayer.setCursor(1, 0);

                    pinLengthCounter = 0;
                    zx = 20;
                    return;
                }
                else if (value > (byte) 0xA) {
                    // Only numeric values in pin
                    zx = 20;
                    return;
                }

                pin[pinLengthCounter++] = value;
                lcdDisplayer.displayString("*");

                if (pinLengthCounter == 4) {

                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Processing...");
                    zx = 40;
                }
                else {
                    zx = 20; // Read again every time, to reset value
                }

            }
            else if (millis() > timeoutStart + TIMEOUT_PIN_DELTA) {

                #ifndef nDebug
                Serial.println("zx = 30; Timeout");
                #endif
                lcdDisplayer.clearDisplay();
                lcdDisplayer.displayString("Scan admin card");

                zx = 10;
            }
            break;

        // Send data to server
        case 40:

                #ifndef nDebug
                Serial.print("zx = 40; Pin code:");
                for (int i = 0; i < PIN_LENGTH; i++) {
                    Serial.print(pin[i], HEX);
                }
                Serial.println("");
                #endif

            espConnection.sendCmdToEsp(SERIALCOMMAND_BARMAN_AUTHENTICATION);

            // Send uid
            for (size_t i = 0; i < RFID_UID_SIZE; i++) {
                espConnection.sendCmdToEsp(uId[i]);
            }

            // Send pin
            for (size_t i = 0; i < PIN_LENGTH; i++) {
                // Send the decimal '0' as char, not 0x0
                espConnection.sendCmdToEsp(pin[i] + HEX_TO_DECIMAL_OFFSET);
            }
            zx = 50;
            break;

        // Wait for server answer
        case 50:

            if (espConnection.hasAnswer()) {

                byte answer = espConnection.readAnswerFromEsp();

                #ifndef nDebug
                Serial.print("zx = 50; Answer: 0x");
                Serial.println(answer, HEX);
                #endif

                if (answer == SERIALCODE_LOGIN_OK) {


                    zx = 60;
                }
                else {

                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Invalid...");
                    lcdDisplayer.setCursor(1,0);
                    lcdDisplayer.displayString("Scan admin card");

                    zx = 10;
                }
            }
            break;

        // Barman Welcome
        case 60:
            nmpController.read();
            lcdDisplayer.clearDisplay();
            lcdDisplayer.displayString("A: Pay, B: Re");
            lcdDisplayer.setCursor(1,0);
            lcdDisplayer.displayString("C: New, D: Bye");

            zx = 70;
            break;

        // Wait input A: pay, B: RE, C: NEW, D: Bye
        case 70:
            nmpController.mss();
            if(nmpController.readDone()){
                isDebit = false;
                switch (nmpController.value()){
                    case 0xA: // Debit
                        isDebit = true;
                    case 0xB: // Credit
                        zx = 100;
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Amount:");
                        lcdDisplayer.setCursor(1, 0);
                        amountBufferCounter = 0;
                        break;
                    case 0xC: // New Client
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Scan new card");
                        zx = 200;
                        break;
                    case 0xD: // Bye
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Scan admin card");
                        zx = 10;
                        break;
                    default:
                        zx = 60;
                }
            }
            break;

        // Enable read for transaction
        case 100:

            nmpController.read();
            zx = 110;
            break;

        // Wait on input
        case 110:
            if(resetButton){
                zx = 60;
            }
            nmpController.mss();
            if(nmpController.readDone()){
                if(nmpController.value() == 0xF){ // #
                    amount = 0;
                    if(amountBufferCounter == 3 && amountBuffer[2] > 1){
                        amount = 101;
                    }else {
                        for (int i = 0; i < amountBufferCounter; i++) {
                            amount += amountBuffer[amountBufferCounter - 1 - i] * round(pow(10, i));
                        }
                    }

                    if(amount > 100){
                        amountBufferCounter = 0;
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Amount:");
                        lcdDisplayer.setCursor(1,0);
                        zx = 100;
                    }else{
                        //amount valid
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Scanning client");
                        lcdDisplayer.setCursor(1,0);
                        lcdDisplayer.displayString("amount ");
                        lcdDisplayer.displayDec((int)amount);
                        zx = 120;
                    }
                }else if (nmpController.value() <= 0x9){ // digit
                    if(amountBufferCounter != MAX_DIGITS_AMOUNT){
                        amountBuffer[amountBufferCounter++] = nmpController.value();
                        char *num;
                        switch (nmpController.value()){
                            case 0:
                                num = "0";
                                break;
                            case 1:
                                num = "1";
                                break;
                            case 2:
                                num = "2";
                                break;
                            case 3:
                                num = "3";
                                break;
                            case 4:
                                num = "4";
                                break;
                            case 5:
                                num = "5";
                                break;
                            case 6:
                                num = "6";
                                break;
                            case 7:
                                num = "7";
                                break;
                            case 8:
                                num = "8";
                                break;
                            case 9:
                                num = "9";
                                break;
                        }
                        lcdDisplayer.displayString(num);
                    }
                    zx = 100;
                }else if (nmpController.value() == 0xC){ // clear
                    amountBufferCounter = 0;
                    zx = 100;
                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Amount:");
                    lcdDisplayer.setCursor(1,0);
                }else {
                    zx = 100;
                }
            }

            break;

        case 120:
            if(resetButton){
                zx = 60;
            }
            if(rfidReader.read()){
                //card is present
                uIdSize = rfidReader.getUIdBytes(uId);

                if (uIdSize == RFID_UID_SIZE) {


                    espConnection.sendCmdToEsp(SERIALCOMMAND_TRANSACTION);

                    // Send uid
                    for (size_t i = 0; i < RFID_UID_SIZE; i++) {
                        espConnection.sendCmdToEsp(uId[i]);
                    }

                    espConnection.sendCmdToEsp(isDebit ? amount * -1 : amount);
                    zx = 130;
                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("processing..");
                }else{
                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Invalid UID...");
                }
            }
            break;

        case 130:
            if(espConnection.hasAnswer()){
                lcdDisplayer.clearDisplay();
                zx = 140;
                switch (espConnection.readAnswerFromEsp()){
                    case SERIALCODE_TRANSACTION_OK:
                        if(isDebit){
                            lcdDisplayer.displayString("Payment OK :)");
                        }else{
                            lcdDisplayer.displayString("Credit OK :)");
                        }
                        nmpController.read();
                        break;
                    case SERIALCODE_TRANSACTION_NOT_ENOUGH_CREDIT:
                        lcdDisplayer.displayString("not enough $");
                        nmpController.read();
                        break;
                    case SERIALCODE_TRANSACTION_NOT_VALID_CARD:
                        lcdDisplayer.displayString("Card not valid");
                        nmpController.read();
                        break;
                    case SERIALCODE_TOKEN_NOT_VALID:
                        lcdDisplayer.displayString("Scan admin card");
                        zx = 10;
                        break;
                    default:
                        lcdDisplayer.clearDisplay();
                        lcdDisplayer.displayString("Unkown error");
                        lcdDisplayer.setCursor(1,0);
                        lcdDisplayer.displayString("Scan admin card");
                        zx = 10;
                }
            }
            break;

        case 140:
            nmpController.mss();
            if(nmpController.readDone()) zx = 60;
            break;

        // New User card
        case 200:
            if(resetButton){
                zx = 60;
            }
            if(rfidReader.read()){
                uIdSize = rfidReader.getUIdBytes(uId);

                if (uIdSize == RFID_UID_SIZE) {
                    zx = 210;
                    espConnection.sendCmdToEsp(SERIALCOMMAND_NEW_USER);
                    // Send uid
                    for (size_t i = 0; i < RFID_UID_SIZE; i++) {
                        espConnection.sendCmdToEsp(uId[i]);
                    }
                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Processing...");
                }else{
                    lcdDisplayer.clearDisplay();
                    lcdDisplayer.displayString("Invalid UID...");
                }
            }
            break;

        case 210:
            if(espConnection.hasAnswer()){
                lcdDisplayer.clearDisplay();
                zx = 220;
                switch (espConnection.readAnswerFromEsp()){
                    case SERIALCODE_NEWUSER_OK:
                        lcdDisplayer.displayString("New User OK :)");
                        nmpController.read();
                        break;
                    case SERIALCODE_NEWUSER_ERROR:
                        lcdDisplayer.displayString("Error :(");
                        nmpController.read();
                        break;
                    case SERIALCODE_TOKEN_NOT_VALID:
                        lcdDisplayer.displayString("Scan admin card");
                        zx = 10;
                        break;
                    case SERIALCODE_UNKOWN_ERROR:
                        lcdDisplayer.displayString("Unkown Error");
                        zx = 10;
                        break;
                }
            }

            break;

        case 220:
            nmpController.mss();
            if(nmpController.readDone()) zx = 60;
            break;

        // Connection error
        case 400:
            break;
        }

}