//
// Created by nico on 10.04.20.
//

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