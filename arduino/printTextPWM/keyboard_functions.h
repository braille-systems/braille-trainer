#ifndef H_KEYBOARD_FUNCS
#define H_KEYBOARD_FUNCS

#include"common_declarations.h"

const int joystickButton = 9; //порт, к которому подключена кнопка джойстика
boolean joystickState = true;

const boolean buttonsConWay = true; //если не работают кнопки - попробовать поменять эту переменную
//number of dot = index in array + 1
const int m = 6; //число кнопок
//const int btns[m] = {4, 2, 3, 7, 6, 5}; for v2.0
const int btns[m] = {2, 3, 4, 7, 6, 5}; //pins for v2.1
const int spaceButton = 10;
const int helpButton = 12;
boolean btns_states[m]; //структура данных, описывающая состояние клавиш клавиатуры в ДАННЫЙ момент времени.
boolean inputStates[m]; //структура данных, описывающая состояние клавиш клавиатуры.
//Интерпретация: символ, введенный с клавиатуры и предназначенный для отправки в сериал.

const char lettersForAlert[m] = {'a', 'b', 'e', 'f', 'g', 'h'};

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

void buttons() {
  //-------EXPERIMENTAL UNSTABLE CODE: START--------
  //JOYSTICK BUTTON
  //настроить в зависимости от подключения кнопки джойстика
  /*
  if ((digitalRead(joystickButton) == HIGH) && joystickState) {
    Serial.println("if");
    Serial.println('c');
    Serial.println(joystickState);
    Serial.println(digitalRead(joystickButton));
    joystickState = false;
    Serial.println(joystickState);
    return;
  }
  else if ((digitalRead(joystickButton) == LOW) && !joystickState) {
    Serial.println("else if");
    Serial.println(digitalRead(joystickButton));
    Serial.println(joystickState);
    joystickState = true;
    Serial.println(joystickState);
  }*/
  //-------EXPERIMENTAL UNSTABLE CODE: END--------
  
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
        alert(lettersForAlert[i]);
      // Serial.println('s' + String(i) + '+'); // + или - зависит от того, как подключены кнопки
      keyboard(i, buttonsConWay);
    }
    else if (digitalRead(btns[i]) == LOW && btns_states[i] == buttonsConWay) {
      //кнопка нажата
      btns_states[i] = !buttonsConWay;
      if (prevBut == 's')
        alert(lettersForAlert[i]);
      // Serial.println('s' + String(i) + '-');
      keyboard(i, !buttonsConWay);
    }
  }
}

#endif
