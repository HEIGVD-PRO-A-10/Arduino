/**
 * File : WiFiCommunication.h
 * Project : PayBeer Terminal (Esp32)
 * Date : 13.05.2020
 * Author : Denis Bourqui, Nicolas Müller
 *
 * Description :
 * Controller for WiFi connection. Contains WiFi Credentials and functions for different functionalities.
 *
 */

#ifndef TERMINAL_WIFICOMMUNICATION_H
#define TERMINAL_WIFICOMMUNICATION_H


#include <Arduino.h>
#include <ArduinoJson.h>


class WiFiCommunication {
public:
    /**
     * Connects to the WiFi
     * @return true if connection ok, else false.
     */
    bool connect();

    /**
     * Questening the current wifi status
     * @return true if wifi connected.
     */
    bool isConnected();

    /**
     * Authenticate Barman functionality. This function saves the token.
     * @param uid Barman UID
     * @param password Barman PIN
     * @return SerialCode representing answer, defined in config.h file.
     */
    byte authenticate(String uid, String password);

    /**
     * New User functionality. Registers a new User in the System.
     * @param uid New Uid to register
     * @return SerialCode representing answer, defined in config.h file.
     */
    byte newUser(String uid);

    /**
     * Transaction functionality. Used for credit or debit.
     * @param uid Client UID
     * @param amount Amount can be positive or negative
     * @return SerialCode representing answer, defined in config.h file.
     */
    byte transaction(String uid, String amount);

private:
    const char *SSID = "EEE_2.4Ghz";                        // WiFi SSID
    const char *PASSWORD = "rentschforpresident";           // WiFi Password
    const String SERVER = "http://192.168.1.42:8000";       // Name of Synphony server
    const int CONNECT_TIMEOUT = 60;                         // In seconds
    StaticJsonDocument<512> jsonObject;                     // JSON object for token extraction
    const char* token;                                      // Current Token

    const char* ROOT_CA = "-----BEGIN CERTIFICATE-----\n"   // Trusted Root certificate
                          "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n"
                          "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
                          "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n"
                          "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n"
                          "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
                          "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n"
                          "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n"
                          "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n"
                          "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n"
                          "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n"
                          "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n"
                          "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n"
                          "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n"
                          "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n"
                          "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n"
                          "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n"
                          "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n"
                          "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n"
                          "-----END CERTIFICATE-----";
};

#endif //TERMINAL_WIFICOMMUNICATION_H
