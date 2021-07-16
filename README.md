# Trackle Arduino Library 

[![GitHub version](https://img.shields.io/badge/version-v1.0.0-blue)](https://github.com/trackle-iot/trackle-arduino-library/releases/latest)

If you like **Trackle** - give it a star!

[![GitHub stars](https://img.shields.io/github/stars/trackle-iot/trackle-arduino-library?style=social)](https://github.com/trackle-iot/trackle-arduino-library/stargazers) 
__________

### Trackle Platform is an IoT as-a-service platform that offers all the software and services needed to develop an IoT solution from Device to Cloud.

We provide [software libraries](https://docs.iotready.it/libreria/panoramica) in C / C ++ / Typescript / Javascript for firmware engineers who want to add IoT connectivity to their device. Communication protocols, security, access to the Cloud and all the management of IoT complexities are already integrated in the library. Developers only need to think about application logic and exploit the potential of the Cloud to add intelligence to their product.

We provide [REST APIs](https://docs.iotready.it/cloud-api/introduction) for software engineers who want to manage their fleet of devices directly from their Web Portals or from their Apps for their end customers. The Cloud allows you to manage multiple levels of authentication to the devices allowing you to share the data and events that they publish between Producer - Reseller - Maintainer - End customer, each with their own permissions. 

## Downloads
**Trackle [Arduino Library](https://github.com/trackle-iot/trackle-arduino-library/releases/latest)**

## Supported boards, Ethernet, WiFi...
Trackle supports already a lot of boards, including support for ESP32, Particle, MicroPython, Node.js and many Single Board Computers. 
You can add your own hardware types easily (see [these](https://github.com/trackle-iot/trackle-arduino-library/tree/master/examples) examples for Arduino)!

## Quickstart: ESP32 WiFi

* Get a DeviceID and a private key from Trackle Platform
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

* Get a DeviceID and a private key from Trackle Platform
* Import this library to Arduino IDE. Guide [here](http://arduino.cc/en/guide/libraries)
* In Arduino IDE, select File -> Examples -> Trackle -> ESP32 Prodino Ethernet
* Update your arduino_secrets.h with these information:
```` 
#define PRIVATE_KEY "-----BEGIN EC PRIVATE KEY-----\n....."
#define DEVICE_ID "10af36....."
```` 
* Flash your ESP32 with the sample firmware

When you are connected - you can check it in your device list on Trackle Platform - explore all Trackle's features! You can customize any example for your hardware!

## Documentation and other helpful links

[Full Trackle Documentation](https://docs.iotready.it/) - a complete guide on Blynk features 

[Official Website](https://www.iotready.it/)

**Social Media:**
[LinkedIn](https://www.linkedin.com/company/iotready-s-r-l/)

## Contributing
We accept contributions from our community: stability bugfixes, new hardware support, or any other improvements.  
