#ifndef H_COMMON
#define H_COMMON

int reqState = 0; //хранит информацию о том поступил ли запрос
boolean isConnected = 0;
int prevBut = '0'; //предыдущее состояние кнопки джойстика

//-------HARDWARE-SPECIFIC VARIABLES---------------
/*
#define VERSION (2.0)
const int speaker = 8; //порт к которому подключен динамик //v2.0
const int muteButton = 10; //кнопка звука
//number of dot = index in array + 1
const int m = 6; //число кнопок
const int btns[m] = {4, 2, 3, 7, 6, 5}; //for v2.0
const int n = 6; //число сервоприводов
int posInside[n] = {90, 90, 90, 95, 66, 46};  // "inside" positions //for v2.0
int steps[n] = {20, 31, 31, 43, 42, 32};  // movement from "inside" positions //for v2.0
const int spaceButton = -1;
const int helpButton = -1;*/


#define VERSION (2.1)
const int speaker = 11;  //v2.1 
const int muteButton = 8; //v2.1
//number of dot = index in array + 1
const int m = 6; //число кнопок
const int btns[m] = {2, 3, 4, 7, 6, 5}; //pins for v2.1
const int spaceButton = 10;
const int helpButton = 12;
const int n = 6; //число сервоприводов
int posInside[n] = {99, 63, 90, 81, 57, 37};  // for V2.1
int steps[n] = {-28, -31, -26, -24, -33, -22};  // for V2.1
//-------------------------------------------------

void setAllInside();
void printText(String request);
void joystick();
void alert(int type);

#endif
