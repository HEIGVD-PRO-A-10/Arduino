/**
 * File : config.h
 * Project : PayBeer Terminal (Arduino Mega & Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Constants used for both Arduinos.
 */

#ifndef ARDUINO_CONFIG_H
#define ARDUINO_CONFIG_H


// General
#define PIN_LENGTH          0x4
#define GLOBAL_SETUP_WAIT   5000                    // Used to have time to monitor everything
#define ESP32_CMD_LENGTH    0x1                     // In bytes
#define ESP32_AMOUNT_LENGTH 0x1                     // In bytes


// RFID
#define RFID_UID_SIZE   0x4

// Defintion serial codes
/* MEGA -> ESP */
#define SERIALCOMMAND_BARMAN_AUTHENTICATION  0x20
#define SERIALCOMMAND_TRANSACTION  0x30
#define SERIALCOMMAND_NEW_USER  0x50

/* ESP -> MEGA */
// Success codes 0xd0 -> 0xff

#define SERIALCODE_LOGIN_OK 0xd0
#define SERIALCODE_TRANSACTION_OK 0xd1
#define SERIALCODE_NEWUSER_OK 0xd2
#define SERIALCODE_WIFI_OK 0xff

// Error codes 0xa0 -> 0xcf
#define SERIALCODE_LOGIN_WRONG_PARAM 0xa0
#define SERIALCODE_LOGIN_WRONG_LOGIN 0xa1
#define SERIALCODE_TRANSACTION_NOT_VALID_CARD 0xa2
#define SERIALCODE_TRANSACTION_NOT_ENOUGH_CREDIT 0xa3
#define SERIALCODE_NEWUSER_ERROR 0xa4

#define SERIALCODE_TOKEN_NOT_VALID 0xcd
#define SERIALCODE_UNKOWN_ERROR 0xce
#define SERIALCODE_NO_WIFI 0xcf

#endif //ARDUINO_CONFIG_H
