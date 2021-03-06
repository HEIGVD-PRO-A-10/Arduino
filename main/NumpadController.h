/**
 * File : NumpadController.h
 * Project : PayBeer Terminal (Arduino Mega)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Controller for Numpad buttons.
 *
 * 1) Always call setup() method before anything else
 * 2) Call mss method in each cycle
 *
 *
 * Button identifier map:
 * 0x1 0x2 0x3 0xA
 * 0x4 0x5 0x6 0xB
 * 0x7 0x8 0x9 0xC
 * 0xE 0x0 0xF 0xD
 *
 * No button pushed: 0xFF
 *
 * Use Example:
 *
    NumpadController nmpController;
    nmpController.setup();
    nmpController.mss();

    if (nmpController.readDone()) {

        Serial.print("Numpad Value: ");
        Serial.println((int)nmpController.value());
        nmpController.read();
    }

 */

#ifndef TERMINAL_NUMPADCONTROLLER_H
#define TERMINAL_NUMPADCONTROLLER_H

#define BTN_0_VAL 0x0
#define BTN_1_VAL 0x1
#define BTN_2_VAL 0x2
#define BTN_3_VAL 0x3
#define BTN_4_VAL 0x4
#define BTN_5_VAL 0x5
#define BTN_6_VAL 0x6
#define BTN_7_VAL 0x7
#define BTN_8_VAL 0x8
#define BTN_9_VAL 0x9
#define BTN_A_VAL 0xA
#define BTN_B_VAL 0xB
#define BTN_C_VAL 0xC
#define BTN_D_VAL 0xD
#define BTN_STAR_VAL 0xE
#define BTN_HASHTAG_VAL 0xF

#define NULL_BTN_VAL 0xFF

#define BTN_VAL_ON_LINE_1 {BTN_1_VAL, BTN_2_VAL,  BTN_3_VAL, BTN_A_VAL}
#define BTN_VAL_ON_LINE_2 {BTN_4_VAL, BTN_5_VAL,  BTN_6_VAL, BTN_B_VAL}
#define BTN_VAL_ON_LINE_3 {BTN_7_VAL, BTN_8_VAL,  BTN_9_VAL, BTN_C_VAL}
#define BTN_VAL_ON_LINE_4 {BTN_STAR_VAL, BTN_0_VAL,  BTN_HASHTAG_VAL, BTN_D_VAL}

#include <Arduino.h>

class NumpadController {
public:

    NumpadController();

    /**
     * setup function for pin initializing
     */
    void setup();

    /**
     * MSS. should be called at each cycle.
     */
    void mss();

    /**
     * Initiate read of one push
     */
    void read();

    /**
     * get status of reading
     * @return true when a button is pressed and released again.
     */
    bool readDone();

    /**
     * Abort a reading
     */
    void abortRead();

    /**
     * get the last pushed button
     * @return button id of last pushed button
     */
    byte value();

private:
    /**
     * Function for analysing column inputs and setting lastButtonRead value.
     * @param btnValues. array of the btn values of this line
     * @param zxToGoIfFound. next zx if a button is pressed
     * @param zxToGoIfNotFound. next zx if no button is pressed
     */
    void readColumns(byte btnValues[],
                     unsigned int zxToGoIfPressed,
                     unsigned int zxToGoIfNotPressed);

    /**
     *
     * @return true if all column inputs are LOW.
     */
    bool rowIsOff();

    unsigned int zx;
    unsigned int filter_i;
    unsigned int powerOnTime_i;
    bool isReading;
    byte lastButtonRead;
    byte valueMapping[4][4] = {BTN_VAL_ON_LINE_1,
                                        BTN_VAL_ON_LINE_2,
                                        BTN_VAL_ON_LINE_3,
                                        BTN_VAL_ON_LINE_4};

};


#endif //TERMINAL_NUMPADCONTROLLER_H
