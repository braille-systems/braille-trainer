#ifndef H_JOYSTICK_FUNCS
#define H_JOYSTICK_FUNCS

#include"common_declarations.h"

const int xIn = A0; //порт к которому подключен VRx
const int yIn = A1; //порт к которому подключен VR

int prevJoy = '0'; //предыдущее состояние джойстика

const int critL = 700; //от 600 до 1000
const int critR = 300; //от 0 до 400
const int critD = 250; //от 0 до 400
const int critU = 750; //от 600 до 1000

//void joystick(){}



void joystick() {
  int xVal, yVal;
  xVal = analogRead(xIn); //считывается x
  yVal = analogRead(yIn); //считывается y
  int test = (xVal >= critL) + (xVal <= critR) + (yVal <= critD) + (yVal >= critU); //количество критических состояний, которому удовлетворяет джойстик
  
  if (test >= 2) //если больше или равно 2, то это диагональ - не обрабатываем
    return;
  else if (test == 0) { //если 0, то джойстик в исходном положении
    prevJoy = '0';
    return;
  }
  
  //блок проверок на соответствие критическому состоянию и отсутствия данного критического состояния до этого: чтобы выводить в Serial только при принципиальном изменении
  if (xVal >= critL && prevJoy != 'l') {
    prevJoy = 'l';
    if (prevBut == 's')
      alert('l');
    if (reqState) {
      Serial.println('l');
      reqState = 0;
    }
    return;
  }
  
  if (xVal <= critR && prevJoy != 'r') {
    prevJoy = 'r';
    if (prevBut == 's')
      alert('r');
    if (reqState) {
      Serial.println('r');
      reqState = 0;
    }
    return;
  }
  
  if (yVal >= critU && prevJoy != 'u') {
    prevJoy = 'u';
    if (prevBut == 's')
      alert('u');
    if (reqState) {
      Serial.println('u');
      reqState = 0;
    }
    return;
  }
  
  if (yVal <= critD && prevJoy != 'd') {
    prevJoy = 'd';
    if (prevBut == 's')
      alert('d');
    if (reqState) {
      Serial.println('d');
      reqState = 0;
    }
    return;
  }
}

#endif
