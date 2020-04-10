/**
 * Classe qui permet de gérer facilement l'intéraction avec le LCD Displayer
 *
 * Utilisation:
 * 1) Toujours appeler setup();
 * 2) Peut afficher ce que l'on souhaite
 *
 * L'écran a un curseur interne. Il commence à 0, 0. Ce sont les indices de la ligne et de la colonne.
 * À chaque caractère écrit, il avance le curseur.
 * On peut placer le curseur où on veut avec la méthode setCursor().
 *
 * Exemple Utilisation:
 *
        lcdDisplayer.setup();

        lcdDisplayer.clearDisplay();
        lcdDisplayer.setCursor(0, 0);
        lcdDisplayer.displayString("New card !");

        // Nouvelle ligne
        lcdDisplayer.setCursor(1, 0);
        lcdDisplayer.displayString("No: ");

        for (size_t i = 0; i < size; i++) {
            lcdDisplayer.displayByte(uId[i]);
        }
 *
 */

#ifndef ARDUINO_LCDDISPLAYER_H
#define ARDUINO_LCDDISPLAYER_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define LCD_DISP_NB_ROWS 2
#define LCD_DISP_NB_COLS 16
#define LCD_DISP_LCD_ADR 0x27

class LcdDisplayer {

private:

    LiquidCrystal_I2C lcd;

public:
    LcdDisplayer();

    /**
     * Initialise la classe. Toujours le faire en premier.
     */
    void setup();

    /**
     * Afficher une chaine de caractère sur l'écran.
     *
     * @param string Chaine à afficher
     */
    void displayString(const char* string);

    /**
     * Remet le curseur à 0, 0
     */
    void resetCursor();

    /**
     * Fixe le curseur à un endroit donné.
     *
     * @param row Indice de la ligne, commence à 0
     * @param col Indice de la colonne, commence à 0
     */
    void setCursor(int row, int col);

    /**
     * Vide l'écran
     */
    void clearDisplay();

    /**
     * Écris le byte voulu sur l'écran. L'affiche en hexadécimal.
     *
     * @param toWrite byte à écrire
     */
    void displayByte(byte toWrite);
};

#endif //ARDUINO_LCDDISPLAYER_H
