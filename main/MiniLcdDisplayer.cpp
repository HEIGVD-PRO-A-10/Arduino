/**
* File : MiniLcdDisplayer.cpp
* Project :
* Date : 13.05.2020
* Author : Denis Bourqui, Nicolas Müller
*
* Description :
* implementation of MiniLcdDisplayer class.
*
* Disclaimer :
* This class is not used in our project at the moment and not tested at ALL!
*/


#include "MiniLcdDisplayer.h"

#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define LCD_MINI_DISP_LCD_ADR 0x3D
#define ASCII_NUM_BASE 48

bool MiniLcdDisplayer::setup() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    bool beginOK = display.begin(SSD1306_SWITCHCAPVCC, LCD_MINI_DISP_LCD_ADR);
    return beginOK;
}

void MiniLcdDisplayer::displayAmount(int amount){
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.cp437(true);

    display.write(ASCII_NUM_BASE + (amount / 10));
    display.write(ASCII_NUM_BASE + (amount % 10));
    display.display();
}

void MiniLcdDisplayer::clearScreen() {
    display.clearDisplay();
    display.display();
}

void MiniLcdDisplayer::drawSmiley(bool happy) {
    //TODO implement bitmaps
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.cp437(true);

    display.write(happy? 'O':'K');
    display.write(happy? 'K':'O');
    display.display();

}