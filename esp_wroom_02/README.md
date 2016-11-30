#ESP-WROOM-02

I use ESP-WROOM-02 as a main MCU for the robot.

##Agent

I have developed an [agent](./agent.ino) that runs on ESP-WROOM-02 to control the robot.

###MQTT lib

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

##MQTT messaging

The agent collects data from each sensor devices and send it to MQTT server on Raspberry Pi 3:
```
ESP-WROOM-02 ---- topic: temp ----> mosquitto on Raspberry Pi 3
```

##MQTT-UART bridge

The agent also works as a MQTT-UART bridge between sensors/actuators on Arduino Uno and Mosquitto/RaspberryPi:
```
[Sensors&actuators/ArduinoUno]TxD/RxD<---UART--->RxD/TxD[ESP-WROOM-02]<---MQTT--->[Mosquitto/RaspberryPi]

```
