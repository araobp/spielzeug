# Internet of Toys (IoT)

##Infrastructure

###Device

####Arduino Uno (AVR ATmega16U2)
![arduino-uno](./doc/arduino-uno.png)

####Raspberry Pi (ARM Cortex-A53)
![rpi3](./doc/rpi3.png)

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
This is a standard way. I made [this sample code for Raspberry Pi](./misc/arduino/serial.go) and [this for Arduino](./misc/arduino/sketch_led_blink.ino) to confirm that this configuration works.

###Centralized control: Firmata

[Gobot](https://gobot.io/) controls Arduino Uno from Raspberry Pi 3 via Firmata:

```
 [Raspberry Pi]-----(Firmata/USB)-----[Arduino]

```
![arduino-rpi](./doc/arduino-rpi.png)

This configuration reminds me of [OpenFlow](https://en.wikipedia.org/wiki/OpenFlow). Unfortunately, Firmata protocol does not support SPI, so I do not use Gobot...

##Tools

I really want 3D printer to make parts!

For the time being, papercraft is OK.
