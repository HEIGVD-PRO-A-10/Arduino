/**
 * Crée le 31.03.2020
 *
 * Classe qui permet d'intéragir avec le lecteur RFID
 *
 * Utilisation:
 * - Il faut dans tous les cas appeler la méthode setup() avant
 *   de pouvoir effectuer des lectures
 * - Une fois setup, il est possible de lire si une nouvelle
 *   carte est scannée avec la méthode read()
 * - Dès que l'information est lue, il est possible de la
 *   récupérer ou de l'afficher.
 *
 * Exemple d'utilisation:
 *
    RFIDReader rfidReader;
    rfidReader.setup();
    byte uId[MAX_UID_SIZE];

    if (rfidReader.read()) {

        rfidReader.printUid();
        size_t size = rfidReader.getUIdBytes(uId);

        Serial.print("Return Uid = ");
        for (size_t i = 0; i < size; i++) {
            Serial.print(uId[i], HEX);
        }

        Serial.println("");

    }
 *
 */

#ifndef ARDUINO_RFIDREADER_H
#define ARDUINO_RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         45          // Pin utilisée sur le méga
#define SS_PIN          44          // Pin utilisée sur le méga

class RFIDReader {
private:

    MFRC522 mfrc522;

public:

    /**
     * Initialise le lecteur de carte RFID
     */
    void setup();

    /**
     * Teste si une carte peut être lue et récupère les informations
     * si elle le peut.
     *
     * @return true si quelque chose à pu être lu, false sinon
     */
    bool read();

    /**
     * Affiche l'Uid si une carte a été lue
     */
    void printUid();

    /**
     * Permet de récupérer l'UId qui a été lu. L'information se trouve
     * sous la forme d'un tableau de byte.
     *
     * @param array Tableau qui sera rempli avec les bytes de l'Uid
     *
     * @return le nombre de bytes qui ont pu être écrit dans array
     */
    size_t getUIdBytes(byte *array);
};

#endif //ARDUINO_RFIDREADER_H
