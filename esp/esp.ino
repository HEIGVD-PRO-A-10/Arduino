#include <Arduino.h>


#include "Controller.h"
#include "Base.h"

//MODE
//#define nDebug

Controller controller;

/**
 * Setup function: executed at poweron of board.
 * - setting up Serial connection to Arduino mega
 * - connecting to wifi
 *      if wifi connection fails after timeout, we're stop in endless loop.
 */
void setup(void){
#ifndef nDebug
    pinMode(2,OUTPUT);
	Serial.begin(9600);
    digitalWrite(2,HIGH);
	delay(5000);
    digitalWrite(2,LOW);
#endif

   // controller.setup();
}

/**
 * main loop. looping the entire runtime.
 */
void loop(void){
    delay(2000);
    controller.testPost();
/*
    int nbBytes = Serial.available();
    unsigned char *buffer = (unsigned char*) malloc(nbBytes);

    for( int i = 0; i < nbBytes && i < controller.getRxBufferSize(); ++i){
        buffer[i] = Serial.read();
    }

    //invoke main controller
    controller.process(buffer, nbBytes);

    free(buffer);
*/
}

/**
 * Sending bytes to arduino mega
 * @param bytes data
 * @param nbBytes number of bytes
 */
void writeOnSerial(char *bytes, unsigned int nbBytes){
    for(int i = 0; i < nbBytes; ++i){
        Serial.write(bytes[i]);
    }
}

/**
 * sending string to arduino mega
 * @param msg String to send
 */
void writeOnSerial(String msg){
    Serial.print(msg);
}

