#include "test.h"
void setup(){
    testfunc2();
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
	delay(100);
	Serial.println("yooo");
}
