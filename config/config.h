//
// Created by nico on 19.04.20.
//

#ifndef ARDUINO_CONFIG_H
#define ARDUINO_CONFIG_H

// General
#define PIN_LENGTH      0x4

// ESP Config
#define ESP32_INIT_CODE_OK      "{code:100}"
#define ESP32_INIT_CODE_FAIL    "{code:900}"
#define ESP32_AUTH_CODE_OK      "{code:110}"
#define ESP32_AUTH_CODE_FAIL    "{code:910}"

#define ESP32_COMMAND_CODE_BARMAN_AUTHENTICATION  0x20

// RFID
#define RFID_UID_SIZE   0x4

#endif //ARDUINO_CONFIG_H
