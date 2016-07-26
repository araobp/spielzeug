# Internet of Toys (IoT)

##Goal

####Model 001
![type001](https://docs.google.com/drawings/d/1EXrgaz9V5ETb_SwbJseOQWrdF1Rf3bmqhidnRHBVv6E/pub?w=960&h=600)

##Infrastructure

###Device

####Arduino Uno (AVR ATmega16U2)
[pic of my arduino-uno](./doc/arduino-uno.png)

####Raspberry Pi (ARM Cortex-A53)
[pic of my rpi3](./doc/rpi3.png)

####Parts

|part                  |product name                   |maker        |units    |procured|
|----------------------|-------------------------------|-------------|---------|--------|
|Board PC              |Raspberry Pi 3                 |Raspberry Pi |1        |Y       |
|Micro controller      |Arduino Uno R3                 |Arduino      |1        |Y       |
|Servo motor           |Micro serve g9 SG90            |Tower Pro    |1        |Y       |
|Condensor             |                               |             |1        |Y       |
|AD converer           |[MCP3008](http://ww1.microchip.com/downloads/en/DeviceDoc/21295C.pdf)                        |Microchip    |1        |Y        |
|Thermister            |[MCP9700](http://ww1.microchip.com/downloads/en/DeviceDoc/21942e.pdf)                        |Microchip    |1        |Y        |
|Proxymity sensor      |[HC-SR04](http://www.micropik.com/PDF/HCSR04.pdf)                        |SainSmart    |1        |N       |
|Camera module         |Raspberry Pi Camera Board v1.3 |?            |1        |Y       |
|LED(red)              |                               |             |1        |Y       |
|LED(blue)             |                               |             |1        |Y       |
|CdS                   |MI5                            |Macron       |1        |Y       |
|Piezonelectric sounder|PKM13EPYH4000-A0               |muRata       |1        |Y       |
|Motor driver          |[TA7291P](http://www.promelec.ru/pdf/ta7291p.pdf)|Toshiba      |2        |Y        |
|Double gearbox        |Double gearbox No.168          |Tamiya       |1        |Y       |
|Tank kit              |Tank kit No.108                |Tamiya       |1        |N       |
|USB cable             |                               |             |1        |Y       |
|Universal board       |                               |             |2        |Y       |
|Terminal block        |2pin                           |             |4        |N       |
|Registers             |                               |             |many     |Y       |
|Cables                |                               |             |many     |Y       |


###Protocol between Rapsberry Pi and Arudino Uno

```
Format for setter: seven digits decimal number in ASCII code + '\n'
Format for getter:  three digits decimal number in ASCII code + '\n'
```

####Motor control

write(1), motor(1), right(0), forward(0), power level(255)
```
1100255\n
```

write(1), motor(1), left(1), backward(1), power level(022)
```
1111022\n
```

####Servo motor control

write(1), servo motor(2), unit#0(0), plus(0), 90 degrees(090)
```
1200090\n
```

write(1), servo motor(2), unit#1(1), minus(1), 22 degrees(022)
```
1211022\n
```

####Proximity sensor

read(0), proximity sensor(3), unit#0(0)
```
030\n
```

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

##Gear box

[Reference](http://www.marutsu.co.jp/contents/shop/marutsu/mame/81.html)
