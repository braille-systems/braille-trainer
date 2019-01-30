#include<Servo.h>
const int num = 6;
const int srvPins[num] = {3/*1*/, 10/*2*/, 7/*3*/, 12/*4*/, 5/*5*/, 8/*6*/};  // servo pins
const int stp = 30;
int startPos[num] = {85, 100, 116, 82, 112, 98};  // "inside" positions
int srvSteps[num] = {stp, 2*stp, -stp, -stp, -2*stp, stp};  // movement from "inside" positions
Servo srv [num];
void setup() {
  for (int i=0; i<num; i++){
    srv[i].attach(srvPins[i]);
    srv[i].write(startPos[i]);
    delay(250);
    srv[i].detach();
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
  }
}

void loop() {
  /*serial test*/
  char c = Serial.read();
  if(c=='a'){
      Serial.write(c);
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);
    }
    
  /*motors test*/
  for(int i=0; i<num; i++){
    srv[i].attach(srvPins[i]);
    srv[i].write(startPos[i]);
    delay (500);
    srv[i].write(startPos[i]+srvSteps[i]);
    delay (250);
    srv[i].detach();
  }
}
