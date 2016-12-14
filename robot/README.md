# Agent for the robot

## Architecture

```
 Arduino Uno          ESP-WROOM-02
  [ agent ]<---UART--->[ agent ]<---MQTT--->[ mosquitto ]
      |                    |
  sensors              sensors
  actuators            LEDs
  LEDs
```

## Code

- [ESP-WROOM-02](./esp_wroom_02)
- [Arduino-Uno](./arduino_uno)

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

