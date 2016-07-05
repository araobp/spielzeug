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

##Language

###Device

Golang and JavaScript/Node.js

###IoT platform

Python/Java/Scala

##Device control

###Framework
[Gobot](https://gobot.io/) or [Johnny-Five](http://johnny-five.io/)

```
 [Raspberry Pi]-----(Firmata/USB)-----[Arduino]

```
Unfortunately, Firmata protocol does not support SPI.

###Autonomous

```
 [Raspberry Pi]----GPIO/SPI/I2C---[Arduino]
```

##Tools

I really want 3D printer to make parts!

For the time being, papercraft is OK.
