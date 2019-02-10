#include <Servo.h>
#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_A4  440
#define NOTE_E4  330

const int n = 6; // servos
const int m = 4; // buttons
const int srvPins[n] = {3/*1*/, 10/*2*/, 7/*3*/, 12/*4*/, 5/*5*/, 8/*6*/};  // servo pins
int posInside[n] = {85, 81, 138, 81, 126, 72};  // "inside" positions
int steps[n] = {33, 60, -39, -28, -55, 48};  // movement from "inside" positions
String lastBuf = "000000";
//number of dot = index in array + 1

const int xIn = A1; //порт к которому подключен VRx
const int yIn = A0; //порт к которому подключен VR
const int speaker = 4; //порт к которому подключен динамик
const int critL = 700; //от 600 до 1000
const int critR = 300; //от 0 до 400
const int critD = 250; //от 0 до 400
const int critU = 750; //от 600 до 1000

const int muteButton = 2; //порт к которому подключена кнопка джойстика (выведена отдельно)
const int btns[m] = {4, 6, 9, 11}; //нужно инициализировать кнопки
boolean btns_states[m];

Servo srv[n];

int prevJoy = '0'; //предыдущее состояние джойстика
int prevBut = '0'; //предыдущее состояние кнопки джойстика
int muteButtonState;
int reqState = 0; //хранит информацию о том поступил ли запрос
unsigned long timingSer; //тайминг сервоприводов
unsigned long timingSpeak; //тайминг динамика

void setInside(int srvNum) {
  srv[srvNum].attach(srvPins[srvNum]);
  srv[srvNum].write(posInside[srvNum]);
  timingSer = millis();
  while(millis() - timingSer < 250)
    joystick();
  srv[srvNum].detach();
}

void setOutside(int srvNum) {
  srv[srvNum].attach(srvPins[srvNum]);
  srv[srvNum].write(posInside[srvNum] + steps[srvNum]);
  timingSer = millis();
  while(millis() - timingSer < 250)
    joystick();
  srv[srvNum].detach();
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
  timingSer = millis();
  while(millis() - timingSer < 250)
    joystick();
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

void alert(int type) {      //сигнал
  int note = 0;
  switch(type) {
    case 'l':
      note = NOTE_B4;
      break;
    case 'r':
      note = NOTE_C4;
      break;
    case 'd':
      note = NOTE_A4;
      break;
    case 'u':
      note = NOTE_E4;
      break;
  }
  tone(speaker, note, 100);
  timingSpeak = millis();
  while(millis() - timingSpeak < 100);
  noTone(speaker);
}

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

void buttons() {
  //MUTE BUTTON
  //сообщение о изменении состояния кнопки, если была отжата, то s - sound, если нажата, то m - mute
  muteButtonState = digitalRead(muteButton);
  if(muteButtonState == HIGH && prevBut != 'm') {
    Serial.println('m');
    prevBut = 'm';
  }
  else if (muteButtonState == LOW && prevBut != 's') {
    Serial.println('s');
    prevBut = 's';
  }

  //BUTTONS
  for (int i = 0; i < m; i++) {
    if (digitalRead(btns[i]) == HIGH && btns_states[i] == false) {
      btns_states[i] = true;
      Serial.print(btns_states[i]);
    }
    else if (digitalRead(btns[i]) == LOW && btns_states[i] == true) {
      btns_states[i] = false;
      Serial.print(btns_states[i]);
    }
  }
}

void setup() {
  setAllInside();
  Serial.begin(9600); 
  pinMode(muteButton, INPUT);
  if(digitalRead(muteButton) == HIGH)
    prevBut = 'm';
  else
    prevBut = 's';
  pinMode(speaker, OUTPUT); 
  for (int i = 0; i < m; i++) {
    pinMode(btns[i], INPUT);
    btns_states[i] = false;
  }
}

void loop() {
  buttons();
  joystick();
  if(Serial.available()) {
    String request = Serial.readString();
    if(request[0] != '?')
      printText(request);
    else
      reqState = 1;
  }
}
