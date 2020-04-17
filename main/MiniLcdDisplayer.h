//
// Created by deni on 17/04/2020.
//

#ifndef TERMINAL_MINILCDDISPLAYER_H
#define TERMINAL_MINILCDDISPLAYER_H
#include <Adafruit_SSD1306.h>

class MiniLcdDisplayer {
public:
    bool setup();
    void displayAmount(int amount);
    void drawSmiley( bool happy);
    void clearScreen();
private:
    Adafruit_SSD1306 display;

};


#endif //TERMINAL_MINILCDDISPLAYER_H
