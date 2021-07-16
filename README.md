# Trackle Arduino Library 

[![GitHub version](https://img.shields.io/badge/version-v1.0.0-blue)](https://github.com/trackle-iot/trackle-ESP32-arduino/releases/latest)

If you like **Trackle** - give it a star!

[![GitHub stars](https://img.shields.io/github/stars/trackle-iot/trackle-ESP32-arduino?style=social)](https://github.com/trackle-iot/trackle-ESP32-arduino/stargazers) 
__________

### Trackle Platform is an IoT as-a-service platform that offers all the software and services needed to develop an IoT solution from Device to Cloud.

We provide [software libraries](https://docs.iotready.it/libreria/panoramica) in C / C ++ / Typescript / Javascript for firmware engineers who want to add IoT connectivity to their device. Communication protocols, security, access to the Cloud and all the management of IoT complexities are already integrated in the library. Developers only need to think about application logic and exploit the potential of the Cloud to add intelligence to their product.

We provide [REST APIs](https://docs.iotready.it/cloud-api/introduction) for software engineers who want to manage their fleet of devices directly from their Web Portals or from their Apps for their end customers. The Cloud allows you to manage multiple levels of authentication to the devices allowing you to share the data and events that they publish between Producer - Reseller - Maintainer - End customer, each with their own permissions. 

## Downloads
**Trackle [Arduino Library](https://github.com/trackle-iot/trackle-ESP32-arduino/releases/latest)**

## Supported boards, Ethernet, WiFi...
Trackle supports already a lot of boards. 
This Github project provides the Trackle library for the Espressif chips ESP32 using Arduino IDE.

## Quickstart: Get a Device ID and a private key
* Create an account on https://platform.iotready.it/
* Open "My Devices" section from the drawer
* Click the button "Claim a device"
* Select the link "I don't have a device id", then Continue
* The Device Id will be shown on the screen and the private key file will be download with name xxxx.der where xxxx is Device ID
* To estract the key in PEM format (the one you must use in firmware) you need to run from command line:
```` 
openssl ec -in xxxx.der -inform DER -out xxx.pem -outform PEM
```` 
* You should copy the content of xxxx-pem file into your arduino_secret.h as explained below

## Quickstart: ESP32 WiFi

* Get a Device ID and a private key from Trackle Platform
* Import this library to Arduino IDE. Guide [here](http://arduino.cc/en/guide/libraries)
* In Arduino IDE, select File -> Examples -> Trackle -> ESP32 generic WiFi
* Update your arduino_secrets.h with these information:
```` 
#define PRIVATE_KEY "-----BEGIN EC PRIVATE KEY-----\n....."
#define DEVICE_ID "10af36....."
#define SSID "MY_SSID"
#define PASSWORD "my_password"
```` 
* Flash your ESP32 with the sample firmware

## Quickstart: ESP32 Prodino Ethernet

* Get a Device ID and a private key from Trackle Platform
* Import this library to Arduino IDE. Guide [here](http://arduino.cc/en/guide/libraries)
* In Arduino IDE, select File -> Examples -> Trackle -> ESP32 Prodino Ethernet
* Update your arduino_secrets.h with these information:
```` 
#define PRIVATE_KEY "-----BEGIN EC PRIVATE KEY-----\n....."
#define DEVICE_ID "10af36....."
```` 
* Flash your ESP32 with the sample firmware

When you are connected - you can check it in your device list on Trackle Platform - explore all Trackle's features! You can customize any example for your hardware!
