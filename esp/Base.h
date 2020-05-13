/**
 * File : Base.h
 * Project : PayBeer Terminal (Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Header for common Arduino functions.
 */

#ifndef TERMINAL_BASE_H
#define TERMINAL_BASE_H

//MODE
#define nDebug

void writeOnSerial(char *bytes, unsigned int nbBytes);
void writeOnSerial(String msg);
void writeByteOnSerial(byte b);
void writeIntOnSerial(int i);

#endif //TERMINAL_BASE_H
