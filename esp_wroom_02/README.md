# ESP-WROOM-02

I use ESP-WROOM-02 as an additional micro controller as well as WiFi module for Arduino.

```
[Raspberry Pi 3]
       |
      WiFi
       |
[WiFi router]
       |
      WiFi
       |
[ESP-WROOM-02] UART Tx/Rx ---[Logic converter]--- UART Tx/Rx [Arduino Uno]
       |                                                           |
LED and thermistor                                          Original Shiled
                                                                   |
                                                        sensors and actuators

```

## MQTT lib

Download and unzip this in Arduino IDE's libralies folder:
https://github.com/knolleary/pubsubclient

For MQTT v3.1 brokers (e.g., RabbitMQ), modify the following file and rebuild the source code:

PubSubClient.h
```
#define MQTT_VERSION MQTT_VERSION_3_1
//#ifndef MQTT_VERSION
//#define MQTT_VERSION MQTT_VERSION_3_1_1
//#endif
```
