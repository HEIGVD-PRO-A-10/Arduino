## Installation de la SDK
### pour le MEGA
```Bash
sudo apt-get install arduino.mk

ou 

yay arduino-mk
sudo mv /usr/share/arduino/hardware/archlinux-arduino /usr/share/arduino/hardware/arduino

sudo pacman -S screen
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



## Compiler

### Mega
```
make
make help
sudo make updload
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

