#include <Stepper.h>
#include <Servo.h>

const int STEPS = 100;
const int STEPPER_PIN1 = 4;
const int STEPPER_PIN2 = 5;
const int BUTTON_PIN = 6;

Stepper main(STEPS, STEPPER_PIN1, STEPPER_PIN2);
Servo row1, row2, row3;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  main.setSpeed(10);
  row1.attach (1);
  row2.attach (2);
  row3.attach (3);
  row1.write (0);
  row2.write (0);
  row3.write (0);
}

void loop() {
  char c = Serial.read();
  if(c != -1){//если с компьютера поступила новая буква
    while(digitalRead(BUTTON_PIN) == HIGH){//ждем пока кнопка не будет нажата
      main.step(1);//вращаем основной барабан
      delay(10);
    }
    putOut(charToBraille(c));//выводим букву
  }
  delay(10);//просто ждем
}

void putOut(char brailleCh){
  int num = 10;
  if (brailleCh & 0x01 == 0)
    row1.write (num);
  if (brailleCh & 0x02 == 0)
    row2.write (num);
  if (brailleCh & 0x04 == 0)
    row3.write (num);
  delay(10);
  row1.write (0);
  row2.write (0);
  row3.write (0);
  main.step(20);
  if (brailleCh & 0x08 == 0)
    row1.write (num);
  if (brailleCh & 0x10 == 0)
    row2.write (num);
  if (brailleCh & 0x20 == 0)
    row3.write (num);
  delay(10);
  row1.write (0);
  row2.write (0);
  row3.write (0);
}

char charToBraille (char c) {
  char b = 0x00;
	switch(c){
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 'u':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		b |= 0x01;
		break;
	}
	switch(c){
		case 'b':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'l':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'v':
		case 'w':
		b |= 0x02;
		break;
	}
	switch(c){
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'w':
		b |= 0x04;
		break;
	}
	switch(c){
		case 'u':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'w':
		b |= 0x08;
		break;
	}
	switch(c){
		case 'd':
		case 'e':
		case 'g':
		case 'h':
		case 'j':
		case 'n':
		case 'o':
		case 'q':
		case 'r':
		case 't':
		case 'y':
		case 'z':
		case 'w':
		b |= 0x10;
		break;
	}
	switch(c){
		case 'c':
		case 'd':
		case 'f':
		case 'g':
		case 'i':
		case 'j':
		case 'm':
		case 'n':
		case 'p':
		case 'q':
		case 's':
		case 't':
		case 'x':
		case 'y':
		case 'w':
		b |= 0x20;
		break;
	}
 return b;
}
