/**
 * File : LcdDisplayer.cpp
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Implementation of LcdDisplayer class
 *
*/

#include "LcdDisplayer.h"

LcdDisplayer::LcdDisplayer() : lcd(LCD_DISP_LCD_ADR, LCD_DISP_NB_COLS, LCD_DISP_NB_ROWS) {}

void LcdDisplayer::setup() {

    lcd.init();
    lcd.backlight();
    resetCursor();

}

void LcdDisplayer::displayString(const char *string) {

    lcd.print(string);
}

void LcdDisplayer::resetCursor() {

    lcd.setCursor(0, 0);
}

void LcdDisplayer::setCursor(int row, int col) {

    lcd.setCursor(col, row);
}

void LcdDisplayer::clearDisplay() {

    lcd.clear();
}

void LcdDisplayer::displayByte(byte toWrite) {

    lcd.print(toWrite, HEX);
}

void LcdDisplayer::displayDec(int toWrite) {

    lcd.print(toWrite, DEC);
}