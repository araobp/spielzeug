# Agent for the robot

## Architecture

```
 Arduino Uno          ESP-WROOM-02                             Raspberry Pi 3
  [ agent ]<---UART--->[ agent ]<--MQTT-->[ mosquitto ]<--MQTT-->[ manager]
      |                    |
  sensors              sensors
  actuators            LEDs
  LEDs
```

## Code

- [Agent for ESP-WROOM-02](./esp8266_agent)
- [Agent for Arduino Uno](./arduino_agent)
- [Manager on Raspberry Pi 3](./rpi)

## Config management

Connect your PC to the USB port (USB-UART bridge), then send a command to write config onto the built-in EEPROM of ESP8266:

```
                                                 ESP8266
   [PC]----- USB ----->[FTDI USB-UART bridge]--->[EEPROM]
```

Config command:
```
"c,<wifi_ssid>,<password>,<matt_server>,<mqtt_port>"
```
