#include <Servo.h>
#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_A4  440
#define NOTE_E4  330

#define NOTE_C3  131
#define NOTE_D3  148
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  207

/*
#define NOTE_C3_1  231
#define NOTE_D3_1  248
#define NOTE_E3_1  265
#define NOTE_F3_1  275
#define NOTE_G3_1  296
#define NOTE_A3_1  307
 */

const boolean buttonsConWay = true; //если не работают кнопки - попробовать поменять эту переменную

/* ======= */
const int n = 1; // servos
const int srvPins[n] = {9};  // servo pins
int posInside[n] = {85};  // "inside" positions
int steps[n] = {33};  // movement from "inside" positions
/* ======= */

String lastBuf = "000000";
//number of dot = index in array + 1

const int xIn = A0; //порт к которому подключен VRx
const int yIn = A1; //порт к которому подключен VR
const int speaker = 8; //порт к которому подключен динамик
const int critL = 700; //от 600 до 1000
const int critR = 300; //от 0 до 400
const int critD = 250; //от 0 до 400
const int critU = 750; //от 600 до 1000

const int muteButton = 10; //порт к которому подключена кнопка джойстика (выведена отдельно)
const int m = 6; //число кнопок
const int btns[m] = {2, 3, 4, 5, 6, 7};
boolean btns_states[m]; //структура данных, описывающая состояние клавиш клавиатуры в ДАННЫЙ момент времени.

boolean inputStates[m]; //структура данных, описывающая состояние клавиш клавиатуры.
//Интерпретация: символ, введенный с клавиатуры и предназначенный для отправки в сериал.

boolean isConnected = 0;

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
//    case 1:
//      note = NOTE_C3;
//      break;
//    case '2':
//      note = NOTE_D3;
//      break;
//    case '3':
//      note = NOTE_E3;
//      break;
//    case '4':
//      note = NOTE_F3;
//      break;
//    case '5':
//      note = NOTE_G3;
//      break;
//    case '6':
//      note = NOTE_A3;
//      break;
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
  //сообщение об изменении состояния кнопки, если была отжата, то s - sound, если нажата, то m - mute
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
    if (digitalRead(btns[i]) == HIGH && btns_states[i] == !buttonsConWay) {
      //кнопка отжата
      btns_states[i] = buttonsConWay;
      if (prevBut == 's')
        alert('d');
      // Serial.println('s' + String(i) + '+'); // + или - зависит от того, как подключены кнопки
      keyboard(i, buttonsConWay);
    }
    else if (digitalRead(btns[i]) == LOW && btns_states[i] == buttonsConWay) {
      //кнопка нажата
      btns_states[i] = !buttonsConWay;
      if (prevBut == 's')
        alert('u');
      // Serial.println('s' + String(i) + '-');
      keyboard(i, !buttonsConWay);
    }
  }
}

void keyboard(int i, boolean b) {
  //Проверяет, пустой ли массив, и выводит в сериал строку вида 110000, если до этого буква (т.е. строка вида 110000) была введена, но не была выведена.

  //Каждое нажатие кнопки изменяет i-й элемент inputStates на true.
  //Если btns_states стал пустым - нужно вывести в сериал строку вида 110000, полученную из inputStates вида [true, true, false, false, false, false].
  //После этого inputStates нужно вернуть в исходное положение.
  
  if (b == true) {
    inputStates[i] = true;
  }
  
  for (int k = 0; k < m; k++) {
    if (btns_states[k] == true) return;
  }

  String s = "";
  for (int k = 0; k < m; k++) {
    s = s + String(inputStates[k]);
  }
  if (reqState) {
    Serial.println(s);
    reqState = 0;
  }
  
  if (!isConnected) {
    // Serial.println(s); //раскомм., если нужно печатать в сериал то, что ввел пользователь с помощью клавиатуры
    printText(s);
  }
  
  for (int k = 0; k < m; k++) {
    inputStates[k] = false;
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

  //клавиатура
  for (int i = 0; i < m; i++) {
    pinMode(btns[i], INPUT);
    btns_states[i] = true;
  }

  for (int i = 0; i < m; i++) {
    inputStates[i] = false;
  }
}

void loop() {
  buttons();
  joystick();
  if (Serial.available()) {
    String request = Serial.readString();
    
    if (request[0] == '!') {
      isConnected = 1;
    }
    else if(request[0] == '?'){
      reqState = 1;
    }
    else
      printText(request);
  }
}
