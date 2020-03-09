#include "test.h"
#include "test2.h"
void setup(){
    testfunc2();
    testfunc3();
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
	delay(1000);
	Serial.println("yooo");
}
