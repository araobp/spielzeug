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
## Temeperature sensor

ESP-WROOM-02's TOUT accepts 0 ~ 1V input range. Use MCP9700-E/TO thermistor.

```
Vout(mV) = 500(mV) + 10 * T(degress celsius),
which means:
- Vout = 500mv at 0 degress celsius
- Vout = 1v at 50 degress celsius

T = ( Vout(mv) - 500(mv) ) / 10
```

Circuit
```
   3.3V
    |
    |
[MCP9700]--->TOUT 
    |
    |
   GND
```

If the precision is no good, use HDC1000 instead (e.g., [AE-HDC1000](http://akizukidenshi.com/catalog/g/gM-08775/)).
   
## MQTT messaging

```
ESP-WROOM-02 ---- topic: temp ----> mosquitto on Raspberry Pi 3
```

### MQTT lib

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

### MQTT message monitoring at Raspberry Pi 3

```
pi@raspberrypi:~/node_modules/mqtt $ node mqtt.js sub -t temp
{"device_id":"5C:CF:7F:08:29:F3","temp":19}
{"device_id":"5C:CF:7F:08:29:F3","temp":20}
{"device_id":"5C:CF:7F:08:29:F3","temp":19}
{"device_id":"5C:CF:7F:08:29:F3","temp":19}
{"device_id":"5C:CF:7F:08:29:F3","temp":19}
{"device_id":"5C:CF:7F:08:29:F3","temp":18}
                :
```
