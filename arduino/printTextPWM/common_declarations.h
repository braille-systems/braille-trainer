#ifndef H_COMMON
#define H_COMMON

int reqState = 0; //хранит информацию о том поступил ли запрос
boolean isConnected = 0;
int prevBut = '0'; //предыдущее состояние кнопки джойстика

void setAllInside();
void printText(String request);
void joystick();
void alert(int type);

#endif
