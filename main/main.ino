#include "MainController.h"

#define MAX_UID_SIZE 10    // UID ne fera jamais plus que 10 bytes

MainController mainController;

void setup() {

    delay(5000);

    Serial.begin(9600);		// Init du serial
    while (!Serial);		// Attends que le serial soit fonctionnel

    mainController.setup();

}

void loop() {

    mainController.mss();
}