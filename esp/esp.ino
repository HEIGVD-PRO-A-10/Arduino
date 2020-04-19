#include <Arduino.h>


#include "Controller.h"
#include "Base.h"

//MODE
#define DEBUG

Controller controller;

/**
 * Setup function: executed at poweron of board.
 * - setting up Serial connection to Arduino mega
 * - connecting to wifi
 *      if wifi connection fails after timeout, we're stop in endless loop.
 */
void setup(void){
#ifdef DEBUG
    pinMode(2,OUTPUT);
	Serial.begin(9600);
    digitalWrite(2,HIGH);
	delay(5000);
    digitalWrite(2,LOW);
#endif

    controller.setup();
}

/**
 * main loop. looping the entire runtime.
 */
void loop(void){
    int nbBytes = Serial.available();
    unsigned char *buffer = (unsigned char*) malloc(nbBytes);

    for( int i = 0; i < nbBytes && i < controller.getRxBufferSize(); ++i){
        buffer[i] = Serial.read();
    }

    //invoke main controller
    controller.process(buffer, nbBytes);

    free(buffer);
}

void writeOnSerial(char *bytes, unsigned int nbBytes){
    for(int i = 0; i < nbBytes; ++i){
        Serial.write(bytes[i]);
    }
}

void writeOnSerial(String msg){
    Serial.print(msg);
}

