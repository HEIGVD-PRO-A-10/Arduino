## Installation de la SDK
### pour le MEGA
```Bash
sudo apt-get install arduino.mk

# ou 

yay arduino
yay arduino-mk
sudo mv /usr/share/arduino/hardware/archlinux-arduino /usr/share/arduino/hardware/arduino

sudo pacman -S screen

# Au besoin:
sudo pacman -S arduino-avr-core

# Pour installer les libraires du RFID
# 1. cloner les sources dans un workspace
git clone git@github.com:miguelbalboa/rfid.git
# 2. déplacer les sources au bon endroit
sudo mkdir /usr/share/arduino/hardware/arduino/avr/libraries/MFRC522
cp -r rfid/* /usr/share/arduino/hardware/arduino/avr/libraries/MFRC522

# Pour installer les librairies pour l'écran LCD
# 1. Cloner les sources
git clone git@github.com:johnrickman/LiquidCrystal_I2C.git
# 2. Les déplacer au bon endroit
sudo mkdir /usr/share/arduino/hardware/arduino/avr/libraries/LiquidCrystal_I2C
cp -r LiquidCrystal_I2C/* /usr/share/arduino/hardware/arduino/avr/libraries/LiquidCrystal_I2C


## Pour installes les lib pour le petit écran:
git clone git@github.com:adafruit/Adafruit_SSD1306.git
sudo mv Adafruit_SSD1306/ /usr/share/arduino/hardware/arduino/avr/libraries/
git clone git@github.com:adafruit/Adafruit-GFX-Library.git
sudo mv Adafruit-GFX-Library/ /usr/share/arduino/hardware/arduino/avr/libraries/Adafruit_GFX

```
### pour le esp (Mega est un preréquis)
Installation pip si pas encore installé
```Bash
cd
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
```

```Bash
sudo pip install pyserial
sudo mkdir /usr/share/arduino/hardware/espressif
cd /usr/share/arduino/hardware/espressif
sudo git clone https://github.com/espressif/arduino-esp32.git esp32
cd esp32
sudo git submodule update --init --recursive
cd tools
sudo python3 get.py
```

**WifiClientSecure BUG:**

```Bash

Error message :
In file included from esp.ino:1:0:
/usr/share/arduino/hardware/espressif/esp32/libraries/HTTPClient/src/HTTPClient.h:35:30: fatal error: WiFiClientSecure.h: No such file or directory
compilation terminated.
make: *** [Makefile:277: /tmp/mkESP/esp_esp32/esp_.cpp.o] Error 1
make: *** Waiting for unfinished jobs....
In file included from /usr/share/arduino/hardware/espressif/esp32/libraries/HTTPClient/src/HTTPClient.cpp:40:0:

Resolution :
sudo cp /usr/share/arduino/hardware/espressif/esp32/libraries/WiFiClientSecure/src/* /usr/share/arduino/hardware/espressif/esp32/libraries/WiFi/src
```

### Version 2.0

suivre:

https://github.com/thunderace/Esp8266-Arduino-Makefile#installation-and-test

#### Libs

```Bash
  git clone git@github.com:bblanchon/ArduinoJson.git
  sudo mv ArduinoJson/  .../Esp8266-Arduino-Makefile/esp32-1.0.4/libraries/
```



## Compiler

### Mega
```
make
make help
sudo make upload
```

### Esp
```Bash
make help
make clean
make all
make flash
```

## serial monitor

### Mega

```
sudo make monitor
```



### ESP

```
sudo screen /dev/ttyUSB0
```

