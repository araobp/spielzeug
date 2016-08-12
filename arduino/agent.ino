// 2016/07/26

#include<Servo.h>

#define LED_PIN 13

// sensor/actuator ID
#define LED 0
#define MOTOR 1
#define SERVO_MOTOR 2
#define PROXIMITY_SENSOR 3

// Digital
// Note: PWM on pin 9,10 and 11 does not seem to work after servo.attach() is called. 
#define PIN_MOTOR2_IN2 2  // TA7291P IN2
#define PIN_MOTOR2_IN1 4  // TA7291P IN1
#define PIN_MOTOR2_VREF 5  // PWM: TA7291P VREF
#define PIN_MOTOR1_IN2 7  // TA7291P IN2
#define PIN_MOTOR1_IN1 8  // TA7291P IN1
#define PIN_MOTOR1_VREF 6  // PWM: TA7291P VREF
#define PIN_SERVO 11  // PWM: Tower Pro SG90
#define PIN_ECHO 12  // Sain Smart HC-SR04
#define PIN_TRIGGER 10  // Sain Smart HC-SR04

// Analog in
#define PIN_OPTICAL1 0  // Sharp GP2Y0AAA21YK0F
#define PIN_OPTICAL2 1  // Sharp GP2Y0AAA21YK0F

// Unit No.
#define ULTRASONIC 0
#define OPTICAL1 1
#define OPTICAL2 2
#define MOTOR1 1
#define MOTOR2 2

// Constants
#define C_A 32.0
#define C_B 4.0

// Servo motor class
Servo servo;

// TA7291P direction control
int in1 = HIGH;
int in2 = LOW;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_MOTOR1_IN1, OUTPUT);
  pinMode(PIN_MOTOR1_IN2, OUTPUT);
  pinMode(PIN_MOTOR1_VREF, OUTPUT);
  pinMode(PIN_MOTOR2_IN1, OUTPUT);
  pinMode(PIN_MOTOR2_IN2, OUTPUT);
  pinMode(PIN_MOTOR2_VREF, OUTPUT);
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
  if (Serial.available() > 0) {
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
        if (sign_s == "1") {
          sign = -1;
        } else if (sign_s == "2") {
          sign = 0;
        }
        int value = cmd.substring(4,7).toInt();
        switch(device) {
          case LED:
            if (sign > 0) {
              digitalWrite(LED_PIN, HIGH);
            } else {
              digitalWrite(LED_PIN, LOW);
            }
            Serial.println("0");  // OK
            break;
          case MOTOR:  // Toshiba TA7291P
            switch(sign) {
              case 1:  // forward
                in1 = HIGH;
                in2 = LOW;
                break;
              case -1:  // reverse
                in1 = LOW;
                in2 = HIGH;
                break;
              case 0:  // break
                in1 = HIGH;
                in2 = HIGH;
                break;
            }
            if (value > 150) {
              Serial.println(-1);  // Vref > Vs(3V)
              break;
            }
            switch(unit) {
              case MOTOR1:
                digitalWrite(PIN_MOTOR1_IN1, in1);
                digitalWrite(PIN_MOTOR1_IN2, in2);
                analogWrite(PIN_MOTOR1_VREF, value);
                break;
              case MOTOR2:
                digitalWrite(PIN_MOTOR2_IN1, in1);
                digitalWrite(PIN_MOTOR2_IN2, in2);
                analogWrite(PIN_MOTOR2_VREF, value);
                break;
            }
            Serial.println(0);
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
}
