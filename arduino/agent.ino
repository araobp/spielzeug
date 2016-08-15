// 2016/07/26

#include<Servo.h>

#define LED_PIN 13

// sensor/actuator ID
#define LED 0
#define MOTOR 1
#define SERVO_MOTOR 2
#define PROXIMITY_SENSOR 3
#define PHOTO_MICRO_SENSOR 4

// Digital
// Note: PWM on pin 9,10 and 11 does not seem to work after servo.attach() is called. 
#define PIN_MOTOR_IN2 3  // TA7291P IN2
#define PIN_MOTOR1_IN1 6  // TA7291P IN1
#define PIN_MOTOR2_IN1 5  // TA7291P IN1
#define PIN_SERVO 11  // PWM: Tower Pro SG90
#define PIN_ECHO 12  // Sain Smart HC-SR04
#define PIN_TRIGGER 10  // Sain Smart HC-SR04
#define PIN_PHOTOMICRO1 9  // Omron EE-SX460-P1
#define PIN_PHOTOMICRO2 8  // Omron EE-SX460-P1

// Analog in
#define PIN_OPTICAL1 0  // Sharp GP2Y0AAA21YK0F
#define PIN_OPTICAL2 1  // Sharp GP2Y0AAA21YK0F

// Unit No.
#define ULTRASONIC 0
#define OPTICAL1 1
#define OPTICAL2 2
#define MOTOR1AND2 0
#define MOTOR1 1
#define MOTOR2 2
#define PHOTOMICRO1 1
#define PHOTOMICRO2 2

#define READ 0
#define WRITE 1
#define EVENT 2

// Constants
#define C_A 32.0
#define C_B 4.0

// Timers
#define TIMER_A 50    // 50msec
#define TIMER_B 1000  // 1sec
#define TIMER_C 5000  // 5sec

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
  pinMode(PIN_MOTOR_IN2, OUTPUT);
  pinMode(PIN_MOTOR2_IN1, OUTPUT);
  pinMode(PIN_MOTOR_IN2, OUTPUT);
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

// Omron "EE-SX460-P1" photo micro sensor
int photo_micro(int unit, int *current, int *prev, int pin) { 
  *current = digitalRead(pin);
  //Serial.println(*current);
  if (*current != *prev) {
    Serial.print(EVENT);
    Serial.print(PHOTO_MICRO_SENSOR);
    Serial.print(unit);
    Serial.println("00" + String(*current));
  }
  *prev = *current;
}

unsigned long now = millis();
unsigned long prev_a = now;
unsigned long prev_b = now;
unsigned long prev_c = now;

int current_pm1 = LOW;
int current_pm2 = LOW;
int prev_pm1 = LOW;
int prev_pm2 = LOW;

void periodic_task_a() {
   photo_micro(PHOTOMICRO1, &current_pm1, &prev_pm1, PIN_PHOTOMICRO1);
   //photo_micro(PHOTOMICRO2, &current_pm2, &prev_pm2, PIN_PHOTOMICRO2);
  //Serial.print("task a");
  //Serial.println(now);
}

void periodic_task_b() {
  //Serial.print("task b");
  //Serial.println(now);
}

void periodic_task_c() {
  //Serial.print("task c");
  //Serial.println(now);
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
      if (rw == READ) {
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
            case PHOTO_MICRO_SENSOR:
              switch(unit) {
                case PHOTOMICRO1:
                  photo_micro(PHOTOMICRO1, &current_pm1, &prev_pm1, PIN_PHOTOMICRO1);
                  break;
                case PHOTOMICRO2:
                  photo_micro(PHOTOMICRO2, &current_pm2, &prev_pm2, PIN_PHOTOMICRO2);
                  break;
              }
        }
      } else if (rw == WRITE) {
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
                in1 = value;
                in2 = LOW;
                break;
              case -1:  // reverse
                in1 = LOW;
                in2 = value;
                break;
              case 0:  // break
                in1 = LOW;
                in2 = LOW;
                break;
            }
            switch(unit) {
              case MOTOR1AND2:
                analogWrite(PIN_MOTOR1_IN1, in1);
                analogWrite(PIN_MOTOR_IN2, in2);
                analogWrite(PIN_MOTOR_IN2, in2);
                break;                
              case MOTOR1:
                if (in2 == LOW) {  // forward or break
                  analogWrite(PIN_MOTOR1_IN1, in1);
                  analogWrite(PIN_MOTOR_IN2, in2);
                }
                break;
              case MOTOR2:
                if (in2 == LOW) {  // forward or break
                  analogWrite(PIN_MOTOR2_IN1, in1);
                  analogWrite(PIN_MOTOR_IN2, in2);
                }
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

  // Periodic tasks
  now = millis();
  if (now - prev_a > TIMER_A) {
    periodic_task_a();
    prev_a = now;
  }
  if (now - prev_b > TIMER_B) {
    periodic_task_b();
    prev_b = now;
  }
  if (now - prev_c > TIMER_C) {
    periodic_task_c();
    prev_c = now;
  }
}
