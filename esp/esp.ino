/**
 * File : esp.ino
 * Project : PayBeer Terminal (Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * main file of ESP32 project.
 */

#include <Arduino.h>
#include "Controller.h"
#include "Base.h"
#include "../config/config.h"

Controller controller;

/**
 * Setup function: executed at power on of board.
 * - setting up Serial connection to Arduino mega
 * - connecting to wifi
 *      if wifi connection fails after timeout, we're stop in endless loop.
 */
void setup(void) {

    delay(GLOBAL_SETUP_WAIT);

    bool setupOk;

    /* Led on while setting up*/
    pinMode(2,OUTPUT);
    pinMode(23,OUTPUT);
    digitalWrite(2,HIGH);

    Serial.begin(9600);

    setupOk = controller.setup();

    /* Delay to wait for Arduino setup */
    delay(10 * 1000);

    if (setupOk) {
        Serial.write(SERIALCODE_WIFI_OK);
    }
    else {
        /* Reste ici si pas de connection */
        Serial.write(SERIALCODE_NO_WIFI);
        while(1);
    }

    digitalWrite(2,LOW);

}

/**
 * main loop. looping the entire runtime.
 */
void loop(void) {

    /* Wifi Status led */
    if(controller.wifiConnected()){
        digitalWrite(23,HIGH);
    }else{
        digitalWrite(23,LOW);
    }

    /* Read Incoming bytes from Arduino MEGA */
    int nbBytes = Serial.available();
    unsigned char *buffer = (unsigned char*) malloc(nbBytes);

    for( int i = 0; i < nbBytes && i < controller.getRxBufferSize(); ++i) {
        buffer[i] = Serial.read();
    }

    /* invoke main controller State machine */
    controller.process(buffer, nbBytes);

    /* free memory resources */
    free(buffer);

}

/**
 * Sending bytes to arduino mega
 * @param bytes data
 * @param nbBytes number of bytes
 */
void writeOnSerial(char *bytes, unsigned int nbBytes) {

    for (int i = 0; i < nbBytes; ++i) {
        Serial.write(bytes[i]);
    }
}

/**
 * sending string to arduino mega
 * @param msg String to send
 */
void writeOnSerial(String msg) {

    Serial.print(msg);
}

/**
 * sending byte on Serial
 * @param b byte to write
 */
void writeByteOnSerial(byte b) {

    Serial.write(b);
}

/**
 * sending int on Serial
 * @param i int to write
 */
void writeIntOnSerial(int i) {

    Serial.print(i);
}