#ifndef H_PWM_FUNCS
#define H_PWM_FUNCS

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include"common_declarations.h"

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

const int angleInside = 0;
const int angleOutside = 20;
unsigned long timingSer; //тайминг сервоприводов
const int n = 6; //число сервоприводов
String lastBuf = "000000"; //последняя выведенная брайль-строка

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

/*
 * angleToPulse(int ang)
 * gets angle in degree and returns the pulse width
 * also prints the value on seial monitor
 * written by Ahmad Nejrabi for Robojax, Robojax.com
 */
int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}

void setInside(int srvNum) {
  pwm.setPWM(srvNum, 0, angleToPulse(angleInside));
  timingSer = millis();
  while(millis() - timingSer < 150)
    joystick();
}

void setOutside(int srvNum) {
  pwm.setPWM(srvNum, 0, angleToPulse(angleOutside));
  timingSer = millis();
  delay(150);
  while(millis() - timingSer < 150)
    joystick();
}

void setAllInside() {
  for (int i = 0; i < n; i++) {
    setInside(i);
  }
}

void printString(String buf) {                     
  int i;
  for(i=0; i<6; i++) {
      if(buf.substring(i, i+1) == "1" && lastBuf.substring(i, i+1) == "0")
        setOutside(i);
      if(buf.substring(i, i+1) == "0" && lastBuf.substring(i, i+1) == "1")
        setInside(i);
  }
  lastBuf = buf;
}

void printText(String request) {
  int i = 0;
  String buf;
  while(request.substring(i, i + 1) != '\0') {
    buf = request.substring(i,i+7);
    printString(buf);
    i = i + 6;
  }
  Serial.println('+');
}

#endif