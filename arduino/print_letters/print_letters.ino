#include <Servo.h>

const int n = 6;
const int srvPins[n] = {3/*1*/, 10/*2*/, 7/*3*/, 12/*4*/, 5/*5*/, 8/*6*/};  // servo pins
const int stp = 30;
int posInside[n] = {85, 100, 116, 82, 112, 98};  // "inside" positions
int steps[n] = {stp, 2*stp, -stp, -stp, -2*stp, stp};  // movement from "inside" positions

//numver of dot = index in array + 1

Servo srv[n];

void setInside(int srvNum) {
  srv[srvNum].attach(srvPins[srvNum]);
  srv[srvNum].write(posInside[srvNum]);
  delay(250);
  srv[srvNum].detach();
}

void setOutside(int srvNum) {
  srv[srvNum].attach(srvPins[srvNum]);
  srv[srvNum].write(posInside[srvNum] + steps[srvNum]);
  delay(250);
  srv[srvNum].detach();
}

void setAllInside() {
  for (int i = 0; i < n; i++) {
    setInside(i);
  }
}

void setup() {
  setAllInside();
  Serial.begin(9600);
}

void printString(){
  int i; 
  if (Serial.available()) {
    String request = Serial.readString();
    for(i=0; i<6; i++){
      if(request.substring(i, i+1) == "1"){
        setOutside(i);
      }
    }
    delay(1000);
    for(i=0; i<6; i++){
      if(request.substring(i, i+1) == "1"){
        setInside(i);
      }
    }
  }

}

void loop() {
  printString();
}
