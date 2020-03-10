## Installation de la SDK
### pour le MEGA
```Bash
sudo apt-get install arduino.mk

ou 

yay arduino
yay arduino-mk
sudo mv /usr/share/arduino/hardware/archlinux-arduino /usr/share/arduino/hardware/arduino

sudo pacman -S screen

Au besoin:
sudo pacman -S arduino-avr-core

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

