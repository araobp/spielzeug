# Internet of Toys (IoT)

##Goal

####Model 001
![type001](https://docs.google.com/drawings/d/1EXrgaz9V5ETb_SwbJseOQWrdF1Rf3bmqhidnRHBVv6E/pub?w=960&h=600)

|part              |product name                   |maker        |units    |
|------------------|-------------------------------|-------------|---------|
|Board PC          |Raspberry Pi 3                 |Raspberry Pi |1        |
|Micor controller  |Arduino Uno R3                 |Arduino      |1        |
|Servo motor       |Micro serve g9 SG90            |?            |1        |
|AD converer       |MCP3008                        |Microchip    |1        |
|Thermister        |MCP9700                        |Microchip    |1        |
|Proxymity sensor  |HC-SR04                        |SainSmart    |1        |
|Camera module     |Raspberry Pi Camera Board v1.3 |?            |1        |
|LED(red)          |                               |             |1        |
|LED(blue)         |                               |             |1        |
|Luminousity sensor|                               |             |1        |
|Speaker           |PKM13EPYH4000-A0               |muRata       |1        |
|FET               |2SK1122                        |NEC          |2        |
|Twin gear box     |                               |Tamiya       |1        |
|Tank kit          |                               |Tamiya       |1        |

##Infrastructure

###Device

####Arduino Uno (AVR ATmega16U2)
[pic of my arduino-uno](./doc/arduino-uno.png)

####Raspberry Pi (ARM Cortex-A53)
[pic of my rpi3](./doc/rpi3.png)

####Parts

###IoT platform

- Apache ZooKeeper
- Apache Kafka
- Apache Cassandra
- Apache Spark

![IoTPlatform](https://docs.google.com/drawings/d/14bmvJhQgG_oQu2N0SiiUWonsNiNL7f1yPZ_jepIAEMU/pub?w=960&h=411)

###Networking

- Inter-device: GPIO/SPI/I2C/ZigBee/BLE/USB
- Device to IoT platform: Ethernet and WiFi

##Device control

###Centralized control: standard way

```
 [Raspberry Pi]-------USB------------[Arduino]
```

![arduino-rpi](./doc/arduino-rpi.png)

This is a standard way. I made [this sample code for Raspberry Pi](./misc/arduino/serial.go) and [this for Arduino](./misc/arduino/sketch_led_blink.ino) to confirm that this configuration works.

###Centralized control: Firmata

[Gobot](https://gobot.io/) controls Arduino Uno from Raspberry Pi via Firmata (MIDI-based protocol):

```
 [Raspberry Pi]-----(Firmata/USB)-----[Arduino]

```

This configuration reminds me of [OpenFlow](https://en.wikipedia.org/wiki/OpenFlow). Unfortunately, Firmata protocol does not support SPI, so I do not use Gobot...

##Tools

I really want 3D printer to make parts!

For the time being, papercraft is OK.
