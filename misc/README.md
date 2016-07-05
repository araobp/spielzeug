##Testing parts with Gobot

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

