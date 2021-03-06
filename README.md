# Trackle library for Arduino Core

````
                     __     _         _ 
  _                 |    __| |       (_)   
 / |_  _ __ ___  ___|   / /| | ___    _  ___  
/_ __||  _/|__ \/ __|  / / | |/ _ \  | |/ _ \ 
 | |__| |  / _ | (__| /  \ | |  __/ _| | (_) |
  \__/|_|  \___/\___|/  \_\|_|\___|(_)_|\___/
````


[![GitHub version](https://img.shields.io/badge/version-v1.0.2-blue)](https://github.com/trackle-iot/trackle-arduino-library/releases/latest) &nbsp; &nbsp;
[![GitHub stars](https://img.shields.io/github/stars/trackle-iot/trackle-arduino-library?style=social)](https://github.com/trackle-iot/trackle-arduino-library/stargazers) 
__________

## What is Trackle

Trackle is an IoT platform that offers all the software and services needed to develop an IoT solution from Device to Cloud. [Trackle website](https://www.trackle.io)

## Overview
This document provides step by step instructions to install the Trackle library and connect your device to Trackle Cloud.
You can use Arduino IDE or VS Code (Microsoft Visual Studio Code) with PlatformIO IDE extension.

### Supported hardware
Trackle library for Arduino Core now supports only ESP32 based boards.

### Download
**Trackle [Library for Arduino Core](https://github.com/trackle-iot/trackle-arduino-library/releases/latest)**

### Installation
* If you are using Arduino IDE:
  * import this library as explained [here](http://arduino.cc/en/guide/libraries)
  * configure ESP32 boards as explained [here](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)
* If you are using VS Code (Microsoft Visual Studio Code) with PlatformIO IDE extension:
  * start a new project, select ESP32 board and Arduino as framework
  * edit platformio.ini and add lib_deps = https://github.com/trackle-iot/trackle-arduino-library/archive/refs/tags/1.0.2.zip

### Quickstart: Get a Device ID and a private key
* Create an account on Trackle Cloud (https://trackle.cloud/)
* Open "My Devices" section from the drawer
* Click the button "Claim a device"
* Select the link "I don't have a device id", then Continue
* The Device Id will be shown on the screen and the private key file will be download with name xxxx.der where xxxx is Device ID
* To estract the key in PEM format (the one you must use in firmware) you need to run from command line:
```` 
openssl ec -in xxxx.der -inform DER -out xxx.pem -outform PEM
```` 
* You should copy the content of xxxx-pem file into your arduino_secret.h as explained below

### Quickstart: ESP32 WiFi

* Get a Device ID and a private key from Trackle Cloud
* In Arduino IDE, select File -> Examples -> Trackle -> ESP32 generic WiFi
* In VS Code, open the file esp32_generic_wifi.ino from the example/esp32_generic_wifi folder
* Update your arduino_secrets.h with these information:
```` 
#define PRIVATE_KEY "-----BEGIN EC PRIVATE KEY-----\n....."
#define DEVICE_ID "10af36....."
#define SSID "MY_SSID"
#define PASSWORD "my_password"
```` 
* Flash your ESP32 with the sample firmware

### Quickstart: ESP32 Prodino Ethernet

* Get a Device ID and a private key from Trackle Cloud
* In Arduino IDE, select File -> Examples -> Trackle -> ESP32 Prodino Ethernet
* In VS Code, open the file esp32_prodino_ethernet.ino  from the example/esp32_prodino_ethernet folder
* Update your arduino_secrets.h with these information:
```` 
#define PRIVATE_KEY "-----BEGIN EC PRIVATE KEY-----\n....."
#define DEVICE_ID "10af36....."
```` 
* Flash your ESP32 with the sample firmware

When you are connected - you can check it in your device list on Trackle Cloud - explore all Trackle's features! You can customize any example for your hardware!

## Troubleshooting
While compiling, if you receive some "reference error to trackle::..." try to rename static library .a in src/esp32/ as libTrackle.a or Trackle.a
We found that with some Arduino IDE and PlatformIO plugins versions there is a bug and the compiler looks for the wrong static library file.
