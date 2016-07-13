// 2016/07/07
// For Arduino Uno

#define LED_PIN 13
 
void setup(){
  pinMode(LED_PIN, OUTPUT);
 
  Serial.begin(9600);
}
 
void loop(){
  int inputchar;
 
  inputchar = Serial.read();
 
  if(inputchar != -1 ){
 
    switch(inputchar){
      case 'h':  // high
 
        Serial.print("ACK-HIGH\n");
        digitalWrite(LED_PIN, HIGH);
        break;
      case 'l':  // low
 
        Serial.print("ACK-LOW\n");
        digitalWrite(LED_PIN, LOW);
        break;
    }
  } else {
    // nop
  }
}

