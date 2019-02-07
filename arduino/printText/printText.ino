#include <Servo.h>
#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_A4  440
#define NOTE_E4  330

const int n = 6;
const int srvPins[n] = {3/*1*/, 10/*2*/, 7/*3*/, 12/*4*/, 5/*5*/, 8/*6*/};  // servo pins
int posInside[n] = {85, 81, 138, 81, 126, 72};  // "inside" positions
int steps[n] = {33, 60, -39, -28, -55, 48};  // movement from "inside" positions
String lastBuf = "000000";
//number of dot = index in array + 1

const int xIn = A1; //порт к которому подключен VRx
const int yIn = A0; //порт к которому подключен VR
const int button = 2; //порт к которому подключена кнопка джойстика
const int speaker = 4; //порт к которому подключен динамик
const int critL = 700; //от 600 до 1000
const int critR = 300; //от 0 до 400
const int critD = 250; //от 0 до 400
const int critU = 750; //от 600 до 1000

Servo srv[n];

int prevJoy = '0'; //предыдущее состояние джойстика
int prevBut = '0'; //предыдущее состояние кнопки джойстика
int buttonState;
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
  //while(millis() - timingSpeak < 100);
  delay(100);
  noTone(speaker);
}

void joystick() {
  int xVal, yVal;
  xVal = analogRead(xIn); //считывается x
  yVal = analogRead(yIn); //считывается y
  int test = (xVal >= critL) + (xVal <= critR) + (yVal <= critD) + (yVal >= critU); //количество критических состояний, которому удовлетворяет джойстик

  //сообщение о изменении состояния кнопки, если была отжата, то s - sound, если нажата, то m - mute
  buttonState = digitalRead(button);
  if(buttonState == HIGH && prevBut != 'm') {
    Serial.println('m');
    prevBut = 'm';
  }
  else if (buttonState == LOW && prevBut != 's') {
    Serial.println('s');
    prevBut = 's';
  }
  
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
    Serial.println('l');
    return;
  }
  
  if (xVal <= critR && prevJoy != 'r') {
    prevJoy = 'r';
    if (prevBut == 's')
      alert('r');
    Serial.println('r');
    return;
  }
  
  if (yVal >= critU && prevJoy != 'u') {
    prevJoy = 'u';
    if (prevBut == 's')
      alert('u');
    Serial.println('u');
    return;
  }
  
  if (yVal <= critD && prevJoy != 'd') {
    prevJoy = 'd';
    if (prevBut == 's')
      alert('d');
    Serial.println('d');
    return;
  }
}

void setup() {
  setAllInside();
  Serial.begin(9600); 
  pinMode(button, INPUT);
  if(digitalRead(button) == HIGH)
    prevBut = 'm';
  else
    prevBut = 's';
  pinMode(speaker, OUTPUT); 
}

void loop() {
  joystick();
  if(Serial.available()) {
    String request = Serial.readString();
    if(request[0] != '?')
      printText(request);
    else
      Serial.println("ok");
  }
}
