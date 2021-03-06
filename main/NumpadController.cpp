/**
* File : NumpadController.cpp
* Project : PayBeer Terminal (Arduino Mega)
* Date : 13.05.2020
* Author : Denis Bourqui, Nicolas Müller
*
* Description :
* Implementation of NumpadController class.
*/

#include "NumpadController.h"
#include <Arduino.h>

/* Arduino Pins */
#define COLUMN_1_PIN 34
#define COLUMN_2_PIN 35
#define COLUMN_3_PIN 36
#define COLUMN_4_PIN 37
#define ROW_1_PIN 30
#define ROW_2_PIN 31
#define ROW_3_PIN 32
#define ROW_4_PIN 33

#define FILTER_INPUT_MAX 50
#define POWERON_WAITTIME_MAX 50

NumpadController::NumpadController() :
                                        zx(0),
                                        filter_i(0),
                                        isReading(false),
                                        lastButtonRead(NULL_BTN_VAL)
                                        { }

void NumpadController::setup() {

    //Rows are Output
    pinMode(ROW_1_PIN, OUTPUT);
    pinMode(ROW_2_PIN, OUTPUT);
    pinMode(ROW_3_PIN, OUTPUT);
    pinMode(ROW_4_PIN, OUTPUT);

    //Columns are Input
    pinMode(COLUMN_1_PIN, INPUT);
    pinMode(COLUMN_2_PIN, INPUT);
    pinMode(COLUMN_3_PIN, INPUT);
    pinMode(COLUMN_4_PIN, INPUT);

}

void NumpadController::mss() {

    switch (zx) {
        case 0:

            //wait on user to call read()
            digitalWrite(ROW_1_PIN, LOW);
            digitalWrite(ROW_2_PIN, LOW);
            digitalWrite(ROW_3_PIN, LOW);
            digitalWrite(ROW_4_PIN, LOW);

            isReading = false; // Stop reading

            break;

            // Row 1
        case 2:

            digitalWrite(ROW_4_PIN, LOW);
            digitalWrite(ROW_1_PIN, HIGH);
            zx = 4;
            filter_i = 0;
            break;

        case 4: // ROW 1 activated

            readColumns(valueMapping[0], 5, 6);
            break;

        case 5:

            if (rowIsOff()) { // button is released

                digitalWrite(ROW_1_PIN, LOW);
                zx = 0;
            }
            break;

            // Row 2
        case 6:

            digitalWrite(ROW_1_PIN, LOW);
            digitalWrite(ROW_2_PIN, HIGH);
            filter_i = 0;
            zx = 8;
            break;

        case 8:

            readColumns(valueMapping[1], 9, 10);
            break;

        case 9:

            if (rowIsOff()) { // button is released

                digitalWrite(ROW_2_PIN, LOW);
                zx = 0;
            }
            break;

            // Row 3
        case 10:

            digitalWrite(ROW_2_PIN, LOW);
            digitalWrite(ROW_3_PIN, HIGH);
            filter_i = 0;
            zx = 12;
            break;

        case 12:

            readColumns(valueMapping[2], 13, 14);
            break;

        case 13:

            if (rowIsOff()) { // button is released

                digitalWrite(ROW_3_PIN, LOW);
                zx = 0;
            }
            break;

            // Row 4
        case 14:

            digitalWrite(ROW_3_PIN, LOW);
            digitalWrite(ROW_4_PIN, HIGH);
            filter_i = 0;
            zx = 16;
            break;

        case 16:

            readColumns(valueMapping[3], 17, 2);
            break;

        case 17:

            if (rowIsOff()) { // button is released

                digitalWrite(ROW_4_PIN, LOW);
                zx = 0;
            }
            break;
    }
}

void NumpadController::abortRead() {

    zx = 0;
    isReading = false;
}

bool NumpadController::readDone() {

    return !isReading;
}

byte NumpadController::value() {

    return lastButtonRead;
}

void NumpadController::read() {

    zx = 2;
    isReading = true;
}

bool NumpadController::rowIsOff() {

    bool c1 = digitalRead(COLUMN_1_PIN);
    bool c2 = digitalRead(COLUMN_2_PIN);
    bool c3 = digitalRead(COLUMN_3_PIN);
    bool c4 = digitalRead(COLUMN_4_PIN);

    if (!c1 && !c2 && !c3 && !c4) {
        return true;
    }
    return false;
}

void NumpadController::readColumns(byte btnValues[],
                                   unsigned int zxToGoIfPressed,
                                   unsigned int zxToGoIfNotPressed) {

    bool c1 = digitalRead(COLUMN_1_PIN);
    bool c2 = digitalRead(COLUMN_2_PIN);
    bool c3 = digitalRead(COLUMN_3_PIN);
    bool c4 = digitalRead(COLUMN_4_PIN);

    if (c1 && filter_i == FILTER_INPUT_MAX) {

        lastButtonRead = btnValues[0];
        zx = zxToGoIfPressed;
    }
    else if (c2 && filter_i == FILTER_INPUT_MAX) {

        lastButtonRead = btnValues[1];
        zx = zxToGoIfPressed;
    }
    else if (c3 && filter_i == FILTER_INPUT_MAX) {

        lastButtonRead = btnValues[2];
        zx = zxToGoIfPressed;
    }
    else if (c4 && filter_i == FILTER_INPUT_MAX) {

        lastButtonRead = btnValues[3];
        zx = zxToGoIfPressed;
    }
    else if (!c1 && !c2 && !c3 && !c4) {

        zx = zxToGoIfNotPressed; // No button pressed
    }
    else {

        filter_i++;
    }
}