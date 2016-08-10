// 2016/07/26

#include<Servo.h>

//#define LED_PIN 13

// sensor/actuator ID
#define LED 0
#define MOTOR 1
#define SERVO_MOTOR 2
#define PROXIMITY_SENSOR 3

// Digital
#define PIN_SERVO 9     // PWM: Tower Pro SG90
#define PIN_TRIGGER 13  // Sain Smart HC-SR04
#define PIN_ECHO 12     // Sain Smart HC-SR04

// Analog in
#define PIN_OPTICAL1 0  // Sharp GP2Y0AAA21YK0F
#define PIN_OPTICAL2 1  // Sharp GP2Y0AAA21YK0F

// Unit No.
#define ULTRASONIC 0
#define OPTICAL1 1
#define OPTICAL2 2

// Constants
#define C_A 32.0
#define C_B 4.0

// Servo motor class
Servo servo;

void setup(){
  //pinMode(LED_PIN, OUTPUT);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  servo.attach(PIN_SERVO);
  Serial.begin(9600);
}

// Sharp "GP2Y0AAA21YK0F" optical proximity sensor
int calc_dist(int pin) {
  float vl = (float)analogRead(pin);
  float vo = 5.0*vl/1023.0;
  float distance = C_A / vo - C_B;
  if (distance < 6.0 || distance > 80.0) {
    distance = -1;  
  }
  return (int)distance;
}

void loop(){
  String cmd = Serial.readStringUntil('\n');
  if (cmd != NULL) {
    cmd.trim();
    //Serial.println(cmd);
    int rw = cmd.substring(0,1).toInt();
    int device = cmd.substring(1,2).toInt();
    int unit = cmd.substring(2,3).toInt();
    //Serial.println(rw);
    //Serial.println(device);
    if (rw == 0) {
      switch(device) {
        case PROXIMITY_SENSOR:
          switch(unit) {
            case ULTRASONIC:
              long duration, distance;
              digitalWrite(PIN_TRIGGER, LOW);
              delayMicroseconds(2);
              digitalWrite(PIN_TRIGGER, HIGH);
              delayMicroseconds(10);
              digitalWrite(PIN_TRIGGER, LOW);
              duration = pulseIn(PIN_ECHO, HIGH);
              distance = (duration/2)/29.1;
              if (distance < 2 || distance > 180) {
                Serial.println(-1);  // Out of range 
              } else {
                Serial.println(distance);
              }
              break;
            case OPTICAL1:
              Serial.println(calc_dist(PIN_OPTICAL1));
              break;
            case OPTICAL2:
              Serial.println(calc_dist(PIN_OPTICAL2));
              break;
          }
          break;
      }
    } else {
      String sign_s = cmd.substring(3,4);
      int sign = 1;
      if (sign_s == "0") {
        sign = -1;
      }
      int value = cmd.substring(4,7).toInt();
      switch(device) {
//        case LED:
//          digitalWrite(LED_PIN, value);
//          Serial.println("0");  // OK
//          break;
        case MOTOR:
          //Serial.println("motor");
          //Serial.println(unit);
          //TODO: motor control
          Serial.println(0);  // OK
          break;
        case SERVO_MOTOR:
          // from -90 degrees to +90 degrees
          if (value > 90) {
            Serial.println(-1);
            break; 
          }
          servo.write(sign * value + 90);
          Serial.println(0);
          break;
      }
    }
  }
}
