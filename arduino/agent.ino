032// 2016/07/26
//#define LED_PIN 13
#define LED 0
#define MOTOR 1
#define SERVO_MOTOR 2
#define PROXIMITY_SENSOR 3

#define PIN_TRIGGER 13
#define PIN_ECHO 12
#define PIN_OPTICAL1 0  // Analog in 0
#define PIN_OPTICAL2 1  // Analog in 1

#define ULTRASONIC 0
#define OPTICAL1 1
#define OPTICAL2 2

void setup(){
  //pinMode(LED_PIN, OUTPUT);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(9600);
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
              {
                int value = analogRead(PIN_OPTICAL1);
                Serial.println(value);
              }
              break;
            case OPTICAL2:
              {
                int value = analogRead(PIN_OPTICAL2);
                Serial.println(value);
              }
              break;
          }
          break;
      }
    } else {
      int sign = cmd.substring(3,4).toInt();
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
          Serial.println("0");  // OK
          break;
        case SERVO_MOTOR:
          //Serial.println("servo motor");
          //Serial.println(unit);
          //TODO: servo motor control
          Serial.println("0");  // OK
          break;
      }
      //Serial.println(sign);
      //Serial.println(value);
    }
  }
}
