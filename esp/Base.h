//
// Created by deni on 02/04/2020.
//

#ifndef TERMINAL_BASE_H
#define TERMINAL_BASE_H

//MODE
#define nDebug

void writeOnSerial(char *bytes, unsigned int nbBytes);
void writeOnSerial(String msg);
void writeByteOnSerial(byte b);
void writeIntOnSerial(int i);

#endif //TERMINAL_BASE_H
