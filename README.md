# Internet of Toys (IoT)

![robot_eyes](./doc/robot_eyes.png)

##Goal

I often see robots at museums on weekends.

My favorit robots:
- [Asimo](http://asimo.honda.com/)
- [Pepper](http://www.softbank.jp/en/robot/)
- [PaPeRo](https://en.wikipedia.org/wiki/PaPeRo)
- [Robokyu](http://www.tfd.metro.tokyo.jp/ts/soubi/robo/05.htm)
- [Mindstorms](https://en.wikipedia.org/wiki/Lego_Mindstorms)

I want to make a toy robot on my own.

I am also interested in PLC(Programmable Logic Controller) such as [MELSEC](http://www.mitsubishielectric.com/fa/products/cnt/plc/). Arduino Uno is something like a tiny version of PLC anyway, so I use Arduino Uno as a controller for a robot.

####Model 001
![type001](https://docs.google.com/drawings/d/1EXrgaz9V5ETb_SwbJseOQWrdF1Rf3bmqhidnRHBVv6E/pub?w=960&h=600)

####Current status

September 12th, 2016.

![model001a](./doc/model001a.png)
![model001b](./doc/model001b.png)
![model001d](./doc/model001d.png)

##Infrastructure

###Device

####Arduino Uno (AVR ATmega16U2)

Main controller.

[pic of my arduino-uno](./doc/arduino-uno.png)

####Original shield for Arduino Uno

Control unit for motors.

![shield](./doc/shield.png)

####Raspberry Pi (ARM Cortex-A53)

"IoT gateway" for connectivity to the Internet.

[pic of my rpi3](./doc/rpi3.png)

####WiFi module

[ESP-WROOM-02](http://espressif.com/en/products/hardware/esp-wroom-02/overview) as an additional micro controller as well as for connectivity to the IoT gateway.

![esp-wroom-02](./doc/esp-wroom-02.png)

Thanks to [TORANJISTA GIJYUTSU](http://toragi.cqpub.co.jp/tabid/775/Default.aspx) and [Akizuki Denshi](http://akizukidenshi.com/catalog/g/gK-09758/).

####Parts

|part                  |product name                   |maker        |quantities|procured|
|----------------------|-------------------------------|-------------|---------|--------|
|Single board computer |Raspberry Pi 3                 |Raspberry Pi |1        |Y       |
|Micro controller      |Arduino Uno R3                 |Arduino      |1        |Y       |
|WiFi module           |[ESP-WROOM-02](http://espressif.com/en/products/hardware/esp-wroom-02/overview)|Espressif|1|Y|
|Logic level converter |[8bit bidrectional logic level converter (FXMA408)](http://akizukidenshi.com/catalog/g/gM-04522/)|Akizuki Denshi|1        |Y       |
|Regulator             |TA48M033F                      |Toshiba      |1        |Y       |
|Servo motor           |Micro serve g9 SG90            |Tower Pro    |1        |Y       |
|Capacitor             |100 micro farad (for servo motor)               |Rubycon      |1        |Y       |
|Capacitor             |10 micro farad (for photo micro sensors)                |Rubycon      |1        |Y       |
|Capacitor             |47 micro farad (for TA48M033F)                |Rubycon      |1        |Y       |
|Capacitor             |0.1 micro farad (for TA48M033F)               |             |1        |Y       |
|Tempereature/humidity sensor            |[AE-HDC1000](http://akizukidenshi.com/catalog/g/gM-08775/)                        |Akizuki/TI    |1        |N        |
|Proxymity sensor      |[HC-SR04](http://www.micropik.com/PDF/HCSR04.pdf)|SainSmart    |1        |Y       |
|Proxymity sensor      |[GP2Y0A21YK0F](http://www.sharpsma.com/webfm_send/1489)|Sharp   |2       |Y       |
|Photo micro sensor    |[EE-SX460-P1](https://www.omron.com/ecb/products/pdf/en-ee_sx460_p1.pdf)|Omron |2   |Y   |
|Geomagnetic sensor    |[AE-HMC5883L](http://akizukidenshi.com/catalog/g/gK-09705/)|Akizuki/Honywell|1|N|
|LED(red)              |                               |             |1        |Y       |
|Motor driver          |[TA7291P](http://www.promelec.ru/pdf/ta7291p.pdf)|Toshiba      |2        |Y        |
|Double gearbox        |[Double gearbox 70168](http://www.tamiya.com/japan/products/70168double_gearbox/)|Tamiya       |1        |Y       |
|Track and wheel       |[Track and wheel set 70100](http://www.tamiya.com/japan/kousaku/k_products/70100_t&w.htm)|Tamiya       |1        |Y       |
|Universal plate       |[Universal plate set 70157](http://www.tamiya.com/japan/products/70157plate/index.htm)|Tamiya       |1        |Y       |
|USB cable             |                               |             |1        |Y       |
|Universal board       |                               |             |2        |Y       |
|Terminal block        |2pin                           |             |4        |Y       |
|Registers             |                               |             |many     |Y       |
|Cables                |                               |             |many     |Y       |
|Battery box           |[AA X 6 (9V)](http://akizukidenshi.com/catalog/g/gP-10611/) |             |1        |N       |
|Battery snap          |[BS-IC](http://akizukidenshi.com/catalog/g/gP-00452/)|  | 1 |N  |
|Toggle switch         |                             |             |1        |Y       |
|Vanila shield and pin headers #1|                         |             |1        |Y       |
|Vanila shield and pin headers #2|                         |             |1        |Y       |

![tank](./doc/tank.png)

###Chassis

I am very good at paper craft, so I use paper with wood glue and acrylic paint to make a chassis of the toy:

![chassis](./doc/chassis.png)

###Protocol between Rapsberry Pi and Arudino Uno

I use Raspberry Pi 3 as a remote controller of the robot. The remote controller sends commands to the robot via WiFi or USB cable. The controller also receives events from the robot.

Commands(Request/Response)
```
   [Arduino Uno R3]<---- command ----[Raspberry Pi 3]
```

Events
```
   [Arduino Uno R3]---- event ---->[Raspberry Pi 3]
```

![arduino-rpi](./doc/arduino-rpi.png)

####Commands(Request/Response)

Command format:
```
Format for setter: seven digits decimal number in ASCII code + '\n'
Format for getter: three digits decimal number in ASCII code + '\n'
```

Acknowledgement:
- Setter commands return OK(0) or NG(-1)
- Getter commands return a requested value

#####LED(pin13) control

write(1), led_pin13(0), unit#0(0), plus(0), high(001)
```
1000001\n
```

write(1), led_pin13(0), unit#0(0), plus(0), low(000)
```
1000000\n
```
#####Motor control

```
TA7291P input/output voltage:
Vs = Vref = 9(V)
Vcc = 5(V)
```

![shield_and_tank](./doc/shield_and_tank.png)

|unit# |direction|level|IN1(PWM)|IN2(PWM)|OUT1(V)| 
|------|---------|-----|---|---|----|
|1(right) or 2(left)|0(forward)        |0 ~ 255  |0 ~ 100(*)|0  |0 ~ +3|
|0(right & left)     |1(reverse)        |0 ~ 255  |0  |0 ~ 100(*)|0 ~ -3|
|1(right) or 2(left)|2(break)        |ANY  |0  |0  |0   |
|1(right) or 2(left)|1(reverse) is not accepted|- |- |- |- |

(*) to be adjusted to the level corresponding to max 3V.

write(1), motor(1), right(1), forward(0), Vref level(100)
```
1110100\n
```
![motor_forward](./doc/motor_forward.png)

write(1), motor(1), right & left(0), reverse(1), Vref level(100)
```
1101100\n
```
write(1), motor(1), right(1), break(2), Vref level(000)
```
1112000\n
```
#####Servo motor control

write(1), servo motor(2), unit#1(1), plus(0), 90 degrees(090)
```
1210090\n
```

write(1), servo motor(2), unit#1(1), minus(1), 22 degrees(022)
```
1211022\n
```

The following is PWM images captured by Sain Smart DSO Note II(DS202):

- "1211090" -90 degrees

![ds202_3](./doc/ds202_3.png)

- "1210000" 0 degrees

![ds202_3](./doc/ds202_2.png)

- "1210090" 90 degrees

![ds202_3](./doc/ds202_1.png)

#####Proximity sensor

read(0), proximity sensor(3), unit#0(0)
```
030\n
```
![proximity_sensors](./doc/proximity_sensors.png)

####Events

#####Events detected by proximity sensors

Arduino Uno as the main controller emits distance info events every 5 seconds.

event(2), proximity sensor(3), unit#0(0), value(073)
```
230073\n
```

event(2), proximity sensor(3), unit#1(1), value(020)
```
231020\n
```

event(2), proximity sensor(3), unit#2(2), value(033)
```
232033\n
```

#####Events detected by photo micro sensors (Omron EE-SX-460-P1)

event(2), photo micro sensor(4), right(1), high(001)
```
241001\n
```

event(2), photo micro sensor(4), left(2), low(000)
```
242000\n
```

![layer-1](https://docs.google.com/drawings/d/1_IUCJ2d_mDrADVNzblp95OzeoWL9WBVYllOt7iUtwKM/pub?w=480&h=270)

My toy has just been equipped with Omron's photo micro sensors:

![photo_micro](./doc/photo_micro.png)

###Electric power for the toy

The power source is AA battery 1.5V * 6 = 9V:
- 9V to Arduino Uno
- 9V to the motors via TA7291P motor drivers
- 9V -> 3.3V to ESP-WROOM-02 via TA48M033F

```
Battery 9V (1.5V*6) --+--> Vin on Arduino Uno
                      |
                      +-- TA7291P(0 ~ 3V) --> Motor#1
                      |
                      +-- TA7291P(0 ~ 3V) --> Motor#2
                      |
                      +-- TA48M033F(3.3V) --> ESP-WROOM-02
```

###Serial communication between Arduino Uno and ESP-WROOM-02

ESP-WROOM-02 and Arduino Uno use UART to communicate with each other.

![UART](https://docs.google.com/drawings/d/1aDB81Uy6aha3X3MEjAcQDwg6ZVhnqG4ljFiO93TYRgk/pub?w=680&h=420)

The voltage(5V) at TxD on Arduino Uno:

![5V](./doc/5V.png)

The voltage(3.3V) at RxD on ESP-WROOM-02:

![3.3v](./doc/3.3v.png)


#### Connecting Arduino Uno to ESP-WROOM-02

This is my work:

![work](./doc/work.png)

JSON stream from Arduino Uno to MQTT server on Raspberry Pi 3 via ESP-WROOM-02:
```
$ ./mqtt.js sub -t event
{"device_id":"18:FE:34:EF:53:69","event":230025}
{"device_id":"18:FE:34:EF:53:69","event":231035}
{"device_id":"18:FE:34:EF:53:69","event":232033}
{"device_id":"18:FE:34:EF:53:69","event":230036}
{"device_id":"18:FE:34:EF:53:69","event":231037}
{"device_id":"18:FE:34:EF:53:69","event":232034}
{"device_id":"18:FE:34:EF:53:69","event":230036}
{"device_id":"18:FE:34:EF:53:69","event":231045}
{"device_id":"18:FE:34:EF:53:69","event":232035}
{"device_id":"18:FE:34:EF:53:69","event":230036}
{"device_id":"18:FE:34:EF:53:69","event":231037}
{"device_id":"18:FE:34:EF:53:69","event":232035}
{"device_id":"18:FE:34:EF:53:69","event":230038}
{"device_id":"18:FE:34:EF:53:69","event":231046}
{"device_id":"18:FE:34:EF:53:69","event":232035}
{"device_id":"18:FE:34:EF:53:69","event":230034}
                    :
```

Sendind a command "1210090" to the toy with mqtt.js:
```
$ ./mqtt.js pub -t 18:FE:34:EF:53:69 1210090
```

### Future work

Currently, this is just a plan:
- Apache ZooKeeper for thing management (i.e., toy management in this project)
- Apache Kafka for data buffering
- Apache Cassandra, MongoDB etc for data collection
- Apache Spark, IPython etc for data analysis
