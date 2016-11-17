# ESP-WROOM-02

I use ESP-WROOM-02 as an additional micro controller as well as WiFi module for Arduino.
   
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

## Test code: MQTT-Serial relay

[code](./agent.ino)

```

  Serial <==> [wifi_serial.ino / ESP-WROOM-02] <==> [MQTT Server / Raspberry Pi 3] <==> MQTT client

```

```
pi@raspberrypi:~/node_modules/mqtt $ node mqtt.js sub -t event
{"device_id":"5C:CF:7F:08:29:F3","event":1}
{"device_id":"5C:CF:7F:08:29:F3","event":123}
{"device_id":"5C:CF:7F:08:29:F3","event":test}
                :
```

```
pi@raspberrypi:~/node_modules/mqtt $ node mqtt.js pub -t 5C:CF:7F:08:29:F3 test


On the serial monitor,

test
```
