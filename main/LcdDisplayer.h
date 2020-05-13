/**
 * File : LcdDisplayer.h
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Controller for LCD Display, 2x16 characters.
 * always call setup()
 *
 * The display contains a intern cursor. It begins at 0, 0. Those are line and column indexes.
 * At each character you write, the cursor increments (row only). You have to switch the line manually.
 * you can set the cursor where you want manually with the setCursor() function.
 *
 * Use Example:
 * lcdDisplayer.setup();

        lcdDisplayer.clearDisplay();
        lcdDisplayer.setCursor(0, 0);
        lcdDisplayer.displayString("New card !");

        // Nouvelle ligne
        lcdDisplayer.setCursor(1, 0);
        lcdDisplayer.displayString("No: ");

        for (size_t i = 0; i < size; i++) {
            lcdDisplayer.displayByte(uId[i]);
        }
*/

#ifndef ARDUINO_LCDDISPLAYER_H
#define ARDUINO_LCDDISPLAYER_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define LCD_DISP_NB_ROWS 2
#define LCD_DISP_NB_COLS 16
#define LCD_DISP_LCD_ADR 0x27

class LcdDisplayer {
public:
    LcdDisplayer();

    /**
     * Initialise object. Always needed to be done before use.
     */
    void setup();

    /**
     * Display String on LCD.
     * @param string string to display
     */
    void displayString(const char* string);

    /**
     * reset cursor at 0, 0
     */
    void resetCursor();

    /**
     * Set cursor at given position.
     * @param row line index, starts at 0
     * @param col row index, starts at 0
     */
    void setCursor(int row, int col);

    /**
     * Clear everything on display
     */
    void clearDisplay();

    /**
     * Write numeric value in hex,
     *
     * @param toWrite value to write
     */
    void displayByte(byte toWrite);

    /**
     * Write numeric value in decimal,
     *
     * @param toWrite value to write
     */
    void displayDec(int toWrite);

private:

    LiquidCrystal_I2C lcd; // Display Object
};

#endif //ARDUINO_LCDDISPLAYER_H
