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

##MQTT-UART bridge

The agent also works as a MQTT-UART bridge between sensors/actuators on Arduino Uno and Mosquitto/RaspberryPi:
```
[sensors&actuators/ArduinoUno]TxD/RxD<---UART--->RxD/TxD[ESP-WROOM-02]<---MQTT--->[Mosquitto/RaspberryPi]<--> MQTT client

```

##MQTT messaging

The agent collects data from each sensor devices and send it to MQTT server on Raspberry Pi 3:
```
[sensorss/ArduinoUno]---UART--->[agent/ESP-WROOM-02]--- MQTT topic: "event" --->[mosquitto/RaspberryPi]--> MQTT client
                                    ^
                                    |
                                   I2C
                                    |
                                [sensors]
```

The agent also receives data from MQTT server and transfers it to Arduino Uno to control actuators.
```
[actuators/ArduinoUno]<---UART---[agent/ESP-WROOM-02]<--- MQTT topic: "<mac address>" ---[mosquitto/RaspberryPi]<-- MQTT client
```
