#include<Servo.h>
const int num = 6;
const int srvPins [num] = {4/*1*/, 5/*2*/, 6/*3*/, 
3/*4*/,$
const int stp = 50;
const int startPos [num] = {52, stp-27, 2*stp-5, 0, 
stp, 2$
const int srvSteps [num] = {stp, -stp, -2*stp, stp, 
-stp, $
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
      digitalWrite(LED_BUILTIN, HIGH);   // turn 
the LED o$
      delay(1000);                       // wait 
for a sec$
      digitalWrite(LED_BUILTIN, LOW);
    }

  /*motors test*/
  for(int i=0; i<num; i++){
    srv[i].attach(srvPins[i]);
    srv[i].write(startPos[i]);
    delay (500);
    srv[i].write(startPos[i]+srvSteps[i]);
    delay (250);

