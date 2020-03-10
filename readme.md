## Installation de la SDK
### pour le MEGA
```Bash
sudo apt-get install arduino.mk

ou 

yay arduino-mk
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

## Compiler
### Mega
je sais pas encore
### Esp
```Bash
make help
make clean
make all
make flash
```