/**
 * File : main.ino
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Entry Point of Arduino Mega. Global setup. loop() called at each processor cycle.
 *
 */

#include "MainController.h"

#define MAX_UID_SIZE 10    // UID ne fera jamais plus que 10 bytes

MainController mainController;

void setup() {

    delay(GLOBAL_SETUP_WAIT);

    Serial.begin(9600);		    // Init du serial
    while (!Serial);		    // Attends que le serial soit fonctionnel

    mainController.setup();

    pinMode(6,INPUT_PULLUP);    // reset button

}

void loop() {

    mainController.mss(!digitalRead(6));

}