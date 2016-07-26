// 2016/07/26
#define LED_PIN 13
#define MOTOR 1
#define SERVO_MOTOR 2
#define PROXIMITY_SENSOR 3

void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
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
          //Serial.println("proximity sensor");
          //Serial.println(unit);
          //Serial.println("111");
          //TODO: obtain a value from a proximity sensor
          break;
      }
    } else {
      int sign = cmd.substring(3,4).toInt();
      int value = cmd.substring(4,7).toInt();
      switch(device) {
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
    blink();
  }
}

