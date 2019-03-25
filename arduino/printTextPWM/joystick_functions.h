#ifndef H_JOYSTICK_FUNCS
#define H_JOYSTICK_FUNCS

#include"common_declarations.h"

const int xIn = A1; //порт к которому подключен VRx
const int yIn = A0; //порт к которому подключен VR

int prevJoy = '0'; //предыдущее состояние джойстика

const int critR = 700; //от 600 до 1000//prev 700
const int critL = 350; //от 0 до 400 //prev 300
const int critU = 380; //от 0 до 400 //prev 250
const int critD = 750; //от 600 до 1000 //prev 750

//void joystick(){}



void joystick() {
  int xVal, yVal;
  xVal = analogRead(xIn); //считывается x
  yVal = analogRead(yIn); //считывается y
  int test = (xVal >= critR) + (xVal <= critL) + (yVal <= critU) + (yVal >= critD); //количество критических состояний, которому удовлетворяет джойстик
  
  if (test >= 2) //если больше или равно 2, то это диагональ - не обрабатываем
    return;
  else if (test == 0) { //если 0, то джойстик в исходном положении
    prevJoy = '0';
    return;
  }
  
  //блок проверок на соответствие критическому состоянию и отсутствия данного критического состояния до этого: чтобы выводить в Serial только при принципиальном изменении
  if (xVal >= critR && prevJoy != 'r') {
    prevJoy = 'r';
    if (prevBut == 's')
      alert('r');
    if (reqState) {
      Serial.println('r');
      reqState = 0;
    }
    return;
  }
  
  if (xVal <= critL && prevJoy != 'l') {
    prevJoy = 'l';
    if (prevBut == 's')
      alert('l');
    if (reqState) {
      Serial.println('l');
      reqState = 0;
    }
    return;
  }
  
  if (yVal >= critD && prevJoy != 'd') {
    prevJoy = 'd';
    if (prevBut == 's')
      alert('d');
    if (reqState) {
      Serial.println('d');
      reqState = 0;
    }
    return;
  }
  
  if (yVal <= critU && prevJoy != 'u') {
    prevJoy = 'u';
    if (prevBut == 's')
      alert('u');
    if (reqState) {
      Serial.println('u');
      reqState = 0;
    }
    return;
  }
}

#endif
