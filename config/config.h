//
// Created by nico on 19.04.20.
//

#ifndef ARDUINO_CONFIG_H
#define ARDUINO_CONFIG_H

// General
#define PIN_LENGTH      0x4

// ESP Config
//#define ESP32_INIT_CODE_OK      "{code:100}\n"
//#define ESP32_INIT_CODE_FAIL    "{code:900}\n"
//#define ESP32_AUTH_CODE_OK      "{code:110}\n"
//#define ESP32_AUTH_CODE_FAIL    "{code:910}\n"


// RFID
#define RFID_UID_SIZE   0x4



// Defintion serial codes

/* MEGA -> ESP */
#define SERIALCOMMAND_BARMAN_AUTHENTICATION  0x20

/* ESP -> MEGA */
// Success codes 0xd0 -> 0xff
// Error codes 0xa0 -> 0xcf
#define SERIALCODE_LOGIN_OK 0xd0
#define SERIALCODE_LOGIN_WRONG_PARAM 0xa0
#define SERIALCODE_LOGIN_WRONG_LOGIN 0xa1
#define SERIALCODE_NO_WIFI 0xcf


#endif //ARDUINO_CONFIG_H
