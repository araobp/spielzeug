##Testing parts with Gobot

[Test codes](./gobot)

###LED

It worked OK.

###SG90 (servo motor)

It seems like SG90 works at frequency 100MHz, so I can use the default setting of pi-blaster.c and Gobot's servo functions.

```
$ sudo ./pi-blaster -g 21 -D
MBox Board Revision: 0xa02082
DMA Channels Info: 0x7f35, using DMA Channel: 14
Using hardware:                   PWM
Number of channels:                 1
PWM frequency:                 100 Hz
PWM steps:                       1000
Maximum period (100  %):      10000us
Minimum period (0.100%):         10us
DMA Base:                  0x3f007000
Initialised, Reading /dev/pi-blaster.
```

I tested my SG90 servo motor and confirmed that it moved its arm from 0 to 180 degrees.

##Testing Arduino IDE
 
[Test codes](./arduino)

I gave up using Gobot, since it does not support SPI and I do not require such abstraction for device control.

##Testing IoT platform

[Test codes](./iot_pf)

###Messaging

I am going to use Apache Kafka.

###Thing management

ZooKeeper has been used by Apache Kafka, so I want to share ZooKeeper for thing management too.

I confirmed that my test program worked with ZK.

