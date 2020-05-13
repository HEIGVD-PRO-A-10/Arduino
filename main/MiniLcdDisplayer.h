/**
* File : MiniLcdDisplayer.h
* Project :
* Date : 13.05.2020
* Author : Denis Bourqui, Nicolas Müller
*
* Description :
* Controller for Adafruit SSD1306 display.
*
* Disclaimer :
* This class is not used in our project at the moment and not tested at ALL!
*/

#ifndef TERMINAL_MINILCDDISPLAYER_H
#define TERMINAL_MINILCDDISPLAYER_H
#include <Adafruit_SSD1306.h>

class MiniLcdDisplayer {
public:
    /**
     * Setup function
     */
    bool setup();

    /**
     * Display a numeric value
     * @param amount value to display
     */
    void displayAmount(int amount);

    /**
     * Draw smiley. NOT IMPLEMENTED
     * @param happy whetever the mood of the smiley.
     */
    void drawSmiley( bool happy);

    /**
     * Clear screen. Go to all black
     */
    void clearScreen();

private:
    Adafruit_SSD1306 display;

};


#endif
