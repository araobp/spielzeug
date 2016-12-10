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
