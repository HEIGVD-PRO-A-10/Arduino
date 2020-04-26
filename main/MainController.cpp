/**
 * Main controller
 */

#include <Arduino.h>

#include "MainController.h"

#define TIMEOUT_PIN_DELTA       30 * 1000
#define HEX_TO_DECIMAL_OFFSET   0x30

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

                lcdDisplayer.clearDisplay();
                lcdDisplayer.displayString("Welcome !");

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

        break;

    // Connection error
    case 400:

        break;
    }


}