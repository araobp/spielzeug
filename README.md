## (This project has been suspended. I will come back to this after I have completed the other project "blocks".)

# Internet of Toys (IoT)

![robot_eyes](./doc/robot_eyes.png)

## Background and motivation

The world of IoT is surrounded by a number of critics and a few of engineers who actually get their hands dirty.

Those critics always talk about "big data", although IoT is just about "IP <-> UART/SPI/I2C/GPIO gateway" -- just about a tiny gateway connecting sensors/actuators to the Internet. Such a gateway costs as low as $5.

Making "Internet of Toys" as my personal hobby is fun, because I do not need to worry about the noise from critics.

## IoT applications

I think, from a standpoint of IoT users, there are two types of IoThings:

- "Unified Systems" unifying vertically integrated existing systems with the cloud.
- Robots and sensors taking a person's duty, managed by an application on the cloud.

## Goal of this project

I often see robots at museums on weekends.

My favorit robots:
- [Asimo](http://asimo.honda.com/)
- [Pepper](http://www.softbank.jp/en/robot/)
- [PaPeRo](https://en.wikipedia.org/wiki/PaPeRo)
- [Robokyu](http://www.tfd.metro.tokyo.jp/ts/soubi/robo/05.htm)
- [Mindstorms](https://en.wikipedia.org/wiki/Lego_Mindstorms)

I want to make a toy robot on my own.

I am also interested in PLC(Programmable Logic Controller) such as [MELSEC](http://www.mitsubishielectric.com/fa/products/cnt/plc/). Arduino Uno is something like a tiny version of PLC anyway, so I use Arduino Uno as a controller for a robot.

#### Model 001
![type001](https://docs.google.com/drawings/d/1EXrgaz9V5ETb_SwbJseOQWrdF1Rf3bmqhidnRHBVv6E/pub?w=630&h=400)

## Technologies

I use the following hardware to develop the robot:
- ESP-WROOM-02 (ESP8266) w/ Arduino IDE
- PIC16F1825 w/ PICkit3 an MPLAB X IDE
- And electronic components　I can purchase in Akihabara or on Amazon.
- Raspberry Pi 3 Model B (ARM/Broadcom)

I also use several components from Apache to construct IoT platform for the robot:
- Apache ZooKeeper
- Apache Kafka

#### Current status

[September 12th, 2016](./doc/CURRENT_STATUS.md)

## Infrastructure

### Controller units

#### Main controller : ESP-WROOM-02

I use [ESP-WROOM-02](http://espressif.com/en/products/hardware/esp-wroom-02/overview) as a main controller as well as for connectivity to MQTT server:

![esp-wroom-02](./doc/esp-wroom-02.png)

Thanks to [TORANJISTA GIJYUTSU](http://toragi.cqpub.co.jp/tabid/775/Default.aspx) and [Akizuki Denshi](http://akizukidenshi.com/catalog/g/gK-09758/).

#### Peripheral controller : PIC16F1825

Originally I used Arduino Uno but it was bulky for such a small robot. I am currently migrating from Arduino Uno to PIC16F.

![pic16f1825](./doc/pic16f1825.png)


I have just purchased PICkit3 and PIC16F1825-I/P, and [tried out basic tests with LED, USB-UART bridge, HC-SR04 and other things](./doc/misc/pic16f1825/README.md).

I have also developed an original actuator shield to control a servo motor and DC motors:

![shield](./doc/shield.png)

#### Remote controller : Raspberry Pi 3 (ARM Cortex-A53)

MQTT server and MQTT clients run on Raspberry Pi 3 to control/manage the robot:

[pic of my rpi3](./doc/rpi3.png)

### Power supply board

I have developed an original power supply board for the robot.

Right terminal block (power in): AA(1.5V) x 4 = 6V,
left terminal block (power out): 6V, turn the toggle switch on (left) to turn on the circuit (and the blue LED turns on)

![power supply board3](./doc/power_circuit3.png)

Right pin headers (power out): 5V, left pin headers (power out):3.3V, green jumper pin to input 5V to the power MOSFET's base.

![power supply board1](./doc/power_circuit1.png)

(Just for testing it) I used the power supply board for Christmas:
- [Lighting interior of German ceramic house](./doc/german_house.png)
- [Powering rainbow-color LEDs](./doc/power_supply_test.png)

### I2C sensor board

This I2C sensor board connects to ESP8266:

![i2c sensor board](./doc/i2c_circuit.png)

### Programming languages and IDEs

|Controller        |Language              | IDE         | Role                  |
|------------------|----------------------|-------------|-----------------------|
|ESP8266           |Arduino lang(C/C++)   | Arduino IDE | Main controller       |
|PIC16F1825        |C                     | MPLAB X IDE | Peripheral controller |
|Raspberry Pi 3    |Go                    | Vim         | Robot manager         |

### Parts

[Parts list](./doc/PARTS.md)

### Sensors/actuators

The robot is equipped with proximity sensors(ultra-sonic and infrared ones), a pair of photo micro sensors, a geomagnetic sensor, a gyro sensor, a temperature sensor, motor drivers(TA7291P) and LEDs.

The trajectory of the robot:
```
                           Goal
                           10
                          /
                         +9
                        /
                       +8
                      /
           4+--+--+--+7
            |  5  6
            +3
            |
            +2
            |
            +1
            |
            0
          Start

Running distance: 10 <- counts from photo-micor sensors
Orientation at the goal: North-east <- geomagnetic sensor

Speed/direction control: use proximity sensors and a gyro sensor
to determin the speed/direction at the point.
```

### Circuit diagrams

#### Sensors/actuators connected to Arduino Uno

Arduino Uno is a peripheral controller for the robot. Most of sensors/actuators for the robot are connected to Arduino Uno.

![circuit](https://docs.google.com/drawings/d/1W1SPfQz1a28t77bc4uBEEQULt6kQg9OV3ybjiGFNwjw/pub?w=640&h=400)

#### Sensors connected to ESP-WROOM-02

I use ESP8266 as a main controller for the robot. It also controls I2C sensors that require Vdd (3.3V).

![circuit2](https://docs.google.com/drawings/d/18I_pgsZUnvplvQndcKiZdZVeY_VCXkdooMTkfAHKn44/pub?w=510&h=300)

![i2c_devices2](./doc/i2c_devices2.png)

I have made [test code](./doc/esp_i2c) for those I2C devices and [calibrated HMC5883L](./doc/HMC5883L_L3GD20.md).

#### Power switch control for emergency stop

I use an inverter IC (SN74HC14N) and a power MOSFET to control the power supply to Arduino Uno and the motor driver TA7291P.

![switches](https://docs.google.com/drawings/d/142T6dvYpsqCeAjY8CEPyFbnrM0wG-Z_mCg9EFyrUCuY/pub?w=680&h=400)

The flip-flop circuit works as emergecy stop.

![flip-flop](https://docs.google.com/drawings/d/1nohxvKnRK1qy8eH2Y72xueg6zDirNLbzRaSeWqpTgeo/pub?w=480&h=270)

I have confirmed that the circuit works: [the test result](./doc/FLIPFLOP.md).

When ESP-WROOM-02 has been started, the GPIO is set to LOW => HIGH => LOW to turn on the motor driver. In case of emergency, push the tact switch to turn off the motor driver. Push the switch again to turn it on.

### Serial communication between PIC16F1825 and ESP-WROOM-02

ESP-WROOM-02 and PIC16F1825 use UART to communicate with each other.

![UART](https://docs.google.com/drawings/d/1aDB81Uy6aha3X3MEjAcQDwg6ZVhnqG4ljFiO93TYRgk/pub?w=680&h=420)

The voltage(5V) on TxD:

![5V](./doc/5V.png)

The voltage(3.3V) on RxD:

![3.3v](./doc/3.3v.png)

### Electric power supply

The power source is AA battery 1.5V * 4 = 6V:
- 5V to PIC16F1825
- 6V to the motors via TA7291P motor drivers
- 3.3V to ESP-WROOM-02

```
Battery 6V (1.5V*4) --+-->TA48M05F(5V) --> PIC16F1825
                      |
                      +-- TA7291P(0 ~ 3V) --> Motor#1
                      |
                      +-- TA7291P(0 ~ 3V) --> Motor#2
                      |
                      +-- TA48M033F(3.3V) --> ESP-WROOM-02
```

### Chassis

I am very good at paper craft, so I use paper with wood glue and acrylic paint to make a chassis of the toy:

![chassis](./doc/chassis.png)

### Protocol between Rapsberry Pi and the robot

I use Raspberry Pi 3 as a remote controller of the robot. The remote controller sends commands to the robot via WiFi or USB cable. The controller also receives events from the robot.

#### Commands(Request/Response)

Command format:
```
Format for setter: seven digits decimal number in ASCII code + '\n'
Format for getter: three digits decimal number in ASCII code + '\n'
```

Acknowledgement:
- Setter commands return OK(0) or NG(-1)
- Getter commands return a requested value

##### LED(pin13) control

write(1), led_pin13(0), unit#0(0), plus(0), high(001)
```
1000001\n
```

write(1), led_pin13(0), unit#0(0), plus(0), low(000)
```
1000000\n
```
##### Motor control

```
TA7291P input/output voltage:
Vs = Vref = 6(V)
Vcc = 5(V)
```

![shield_and_tank](./doc/shield_and_tank.png)

Vs = Vref = 6V

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
##### Servo motor control

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

##### Proximity sensor

read(0), proximity sensor(3), unit#0(0)
```
030\n
```
![proximity_sensors](./doc/proximity_sensors.png)

#### Events

##### Events detected by proximity sensors

Arduino Uno as a peripheral controller emits distance info events every 5 seconds.

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

##### Events detected by photo micro sensors (Omron EE-SX-460-P1)

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

##### Events from I2C sensors (3.3V)

events(3), temperature(5), plus(0), value(023)

events(3), geomagnetic(6), minus(1), value(056)

events(4), gyroscope(7), x(0), plus(1), value(00023)

events(4), gyroscope(7), y(1), minus(1), value(00345)

events(4), gyroscope(7), z(2), minus(1), value(00006)

#####Example of event stream from ESP-WROOM-02 to MQTT server on Raspberry Pi 3

Event format:
```
<ESP-WROOM-02's MAC address>,<event>,<event>,...
```

Events from I2C devices on ESP-WROOM-02:
```
$ ./mqtt.js sub -t event
18FE34EF5369,350023,370157
18FE34EF5369,470100000,471000002,472000030
18FE34EF5369,470100001,471000002,472000093
18FE34EF5369,470100001,471000001,472000076
18FE34EF5369,470100010,471100003,472100002
18FE34EF5369,470000005,471000080,472100018
18FE34EF5369,350023,370148
18FE34EF5369,470100033,471100267,472000041
18FE34EF5369,470000018,471100002,472000043
18FE34EF5369,470000032,471000276,472100047
18FE34EF5369,470000002,471000056,472100017
18FE34EF5369,470100001,471100000,472100000
     :
```

Events from sensors on Arduino Uno via ESP-WROOM-02:
```
$ ./mqtt.js sub -t event
18FE34EF5369,230025
18FE34EF5369,231035
18FE34EF5369,232033
18FE34EF5369,230036
18FE34EF5369,231037
18FE34EF5369,232034
18FE34EF5369,230036
18FE34EF5369,231045
18FE34EF5369,232035
18FE34EF5369,230036
18FE34EF5369,231037
18FE34EF5369,232035
       :
```

#### Connecting Arduino Uno to ESP-WROOM-02

This is my work:

![work](./doc/work.png)

## Future work

Use TensorFlow for feedback control.
