# Agent for the robot

## Architecture

```
-- Arduino Uno -- -- ESP-WROOM-02 -- --------------- Raspberry Pi 3 -- - - - - - - - -

   [agent]<---UART--->[agent]<--MQTT-->[mosquitto]<--MQTT-->[manager]-->[Apache Kafka]
      |                  |
    GPIO               GPIO
     PWM                I2C
      |                  |
  sensors             sensors
  actuators           LEDs
  LEDs
```

You see that Internet of Things is just about data flow among things. Why do they misunderstand what IoT is about?

Just focus on the networking aspects! GPIO, I2C, SPI, UART, IPv4, TCP, MQTT and Kafka.

## Code

- [Agent for ESP-WROOM-02](./esp8266_agent)
- [Agent for Arduino Uno](./arduino_agent)
- [Manager on Raspberry Pi 3](./rpi)

## Sensor data streaming

I am going to use Apache Kafka as a conduit to other services (e.g., Cassandra).

I am also planning to use Apache ZooKeeper for device management.

## Config management for ESP8266

Connect your PC to the USB port (USB-UART bridge), then send a command to write config onto the built-in EEPROM of ESP8266:

```
                                                 ESP8266
   [PC]----- USB ----->[FTDI USB-UART bridge]--->[EEPROM]
```

Config command:
```
"c,<wifi_ssid>,<password>,<matt_server>,<mqtt_port>"
```
