/**
 * Main controller
 *
 * Always call setup() method before usage
 * Call mss() in every loop
 *
 */

#include <Arduino.h>

#include "MainController.h"

#define TIMEOUT_PIN_DELTA   30 * 1000

MainController::MainController() : zx(0),
                                   uIdSize(0),
                                   pinLengthCounter(0)
{}

void MainController::setup() {

    Serial.println("Setting up modules...");

    rfidReader.setup();
    Serial.println("RFID Reader OK.");

    espConnection.setup();
    Serial.println("ESP32 OK.");

    nmpController.setup();
    Serial.println("NUMPAD OK.");

    lcdDisplayer.setup();
    Serial.println("LCD OK.");

    Serial.println("Init Done.");

}

void MainController::mss() {

    switch (zx) {

    // Init
    case 0:

        if (espConnection.hasAnswer()) {

            String answer = espConnection.readAnswerFromEsp();

            if (answer.equals(ESP32_INIT_CODE_OK)) {

                zx = 10;
                lcdDisplayer.displayString("Scan admin card...");
            }
            else {

                zx = 400;
            }
        }
        break;

    // Wait for Barman card
    case 10:

        if (rfidReader.read()) {

            uIdSize = rfidReader.getUIdBytes(uId);

            if (uIdSize != RFID_UID_SIZE) {

                lcdDisplayer.clearDisplay();
                lcdDisplayer.displayString("Invalid UID...");
                return;
            }

            pinLengthCounter = 0;

            lcdDisplayer.clearDisplay();
            lcdDisplayer.displayString("Enter PIN code");

            timeoutStart = millis();
            zx = 20;

        }
        break;

    // Start Read
    case 20:

        nmpController.read();
        zx = 30;
        break;

    // Read pin
    case 30:

        if (nmpController.readDone()) {

            byte value = nmpController.value();

            if (value == (byte) 0xC) {

                pinLengthCounter = 0;
                zx = 20;
                return;
            }
            else if (value > (byte) 0xA) {
                // Only numeric values in pin
                zx = 20;
                return;
            }

            pin[pinLengthCounter] = value;
            pinLengthCounter++;

            if (pinLengthCounter == 4) {

                lcdDisplayer.clearDisplay();
                lcdDisplayer.displayString("Processing...");
                zx = 40;
            }
        }
        else if (millis() - TIMEOUT_PIN_DELTA > timeoutStart) {

            zx = 10;
        }
        break;

    // Send data to server
    case 40:

        espConnection.sendCmdToEsp(ESP32_COMMAND_CODE_BARMAN_AUTHENTICATION);

        // Send uid
        for (size_t i = 0; i < RFID_UID_SIZE; i++) {
            espConnection.sendCmdToEsp(uId[i]);
        }

        // Send pin
        for (size_t i = 0; i < PIN_LENGTH; i++) {
            espConnection.sendCmdToEsp(pin[i]);
        }
        zx = 50;
        break;

    // Wait for server answer
    case 50:

        if (espConnection.hasAnswer()) {

            String answer = espConnection.readAnswerFromEsp();

            if (answer.equals(ESP32_AUTH_CODE_OK)) {

                zx = 60;
            }
            else if (answer.equals(ESP32_AUTH_CODE_FAIL)) {

                zx = 10;
            }
        }
        break;

    // Barman Welcome
    case 60:

        lcdDisplayer.clearDisplay();
        lcdDisplayer.displayString("Welcome !");
        break;

    // Connection error
    case 400:

        lcdDisplayer.clearDisplay();
        lcdDisplayer.displayString("No connection...");
        lcdDisplayer.setCursor(1, 0);
        lcdDisplayer.displayString("Reset Arduino");
        break;
    }


}