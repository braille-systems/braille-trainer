#include <Servo.h>

const int n = 6;
const int srvPins[n] = {3/*1*/, 10/*2*/, 7/*3*/, 12/*4*/, 5/*5*/, 8/*6*/};  // servo pins
const int stp = 30;
int posInside[n] = {85, 100, 116, 82, 112, 98};  // "inside" positions
int steps[n] = {stp, 2*stp, -stp, -stp, -2*stp, stp};  // movement from "inside" positions
String lastBuf = "000000";
//numver of dot = index in array + 1

const int xIn = A1; //порт к которому подключен VRx
const int yIn = A0; //порт к которому подключен VRy
const int critL = 300; //от 0 до 400
const int critR = 700; //от 600 до 1000
const int critU = 250; //от 600 до 1000
const int critD = 750; //от 0 до 400

Servo srv[n];

int prev = '0'; //предыдущее состояние джойстика

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

void printString(String buf)
{                     
  int i;
  for(i=0; i<6; i++)
  {
      if(buf.substring(i, i+1) == "1" && lastBuf.substring(i, i+1) == "0")
        setOutside(i);
      if(buf.substring(i, i+1) == "0" && lastBuf.substring(i, i+1) == "1")
        setInside(i);
  }
  lastBuf = buf;
  delay(1000);
}

void printText()
{
  int i = 0;
  String buf;
  String request = Serial.readString();
  while(request.substring(i, i + 1) != '\0')
  {
    buf = request.substring(i,i+7);
    printString(buf);
    i = i + 6;
  }
  Serial.println('+');
}

void joystick()
{
  int xVal, yVal;
  xVal = analogRead(xIn); //считывается x
  yVal = analogRead(yIn); //считывается y
  int test = (xVal >= critR) + (xVal <= critL) + (yVal <= critU) + (yVal >= critD); //количество критических состояний, которому удовлетворяет джойстик
  
  if (test >= 2) //если больше или равно 2, то это диагональ - не обрабатываем
    return;
  else if (test == 0) //если 0, то джойстик в исходном положении
  {
    prev = '0';
    return;
  }
  
  //блок проверок на соответствие критическому состоянию и отсутствия данного критического состояния до этого: чтобы выводить в Serial только при принципиальном изменении
  if (xVal >= critR && prev != 'r') 
  {
    prev = 'r';
    Serial.println('r');
    return;
  }
  
  if (xVal <= critL && prev != 'l')
  {
    prev = 'l';
    Serial.println('l');
    return;
  }
  
  if (yVal >= critD && prev != 'd')
  {
    prev = 'd';
    Serial.println('d');
    return;
  }
  
  if (yVal <= critU && prev != 'u')
  {
    prev = 'u';
    Serial.println('u');
    return;
  }
}

void setup() 
{
  setAllInside();
  Serial.begin(9600);  
}

void loop() 
{
  if(Serial.available())
  {
    printText();
    joystick(); 
  }
}
