/*
   Supported commands:
   - all.off
   - all.on
   - s<digit>.off
   - s<digit>.on
   - s<digit>.off+<digit>
   - s<digit>.off-<digit>
   - s<digit>.on+<digit>
   - s<digit>.on-<digit>
   - p - print two arrays
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

unsigned long timingSer; //тайминг сервоприводов
const int n = 6; //число сервоприводов
//String lastBuf = "000000"; //последняя выведенная брайль-строка
//const int stp = 20;
int posInside[n] = {90, 90, 90, 95, 66, 46};  // "inside" positions
int steps[n] = {20, 29, 31, 46, 45, 25};  // movement from "inside" positions

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

/*
 * angleToPulse(int ang)
 * gets angle in degree and returns the pulse width
 * also prints the value on seial monitor
 * written by Ahmad Nejrabi for Robojax, Robojax.com
 */
int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}

void setInside(int srvNum) {
  pwm.setPWM(srvNum, 0, angleToPulse(posInside[srvNum]));
  delay(150);
  //timingSer = millis();
  //while(millis() - timingSer < 150)
  //  continue; //joystick();
}

void setOutside(int srvNum) {
  pwm.setPWM(srvNum, 0, angleToPulse(posInside[srvNum]-steps[srvNum]));
  //timingSer = millis();
  delay(150);
  //while(millis() - timingSer < 150)
  //  continue; //joystick();
}

void setAllInside() {
  for (int i = 0; i < n; i++) {
    setInside(i);
  }
}

void setAllOutside() {
  for (int i = 0; i < n; i++) {
    setOutside(i);
  }
}

String printArray(int arr[], int arrLength) {
  /*
   * >> 12, 34, 56, 78, 90
   */
  String str = "";
  str += arr[0];
  for (int i = 1; i < arrLength; i++) {
    str += ", ";
    str += arr[i];
  }
  return str;
}

void setup() {
  //setAllInside();
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  Serial.println("Arduino is ready to work.");
}

void loop() {
  if (Serial.available()) {
    String request = Serial.readString();
    if (request.substring(0, 1) == "p") {
      Serial.println("Inner positions:");
      Serial.println(printArray(posInside, n));
      Serial.println("Steps:");
      Serial.println(printArray(steps, n));
    }
    else if (request.substring(0, 1) == "s") {
      String s = request.substring(1, 2);
      int i = s.toInt() - 1;
      if (request.substring(3, 5) == "on") {
        if (request.substring(5, 6) == "+") {
          String strNum = request.substring(6, 7);
          int num = strNum.toInt();
          steps[i] += num;
          Serial.println(s + " in steps (outside pos) array has been increased by " + strNum);
          setOutside(i);
          Serial.println("s" + s + " is on.");
        }
        else if (request.substring(5, 6) == "-") {
          String strNum = request.substring(6, 7);
          int num = strNum.toInt();
          steps[i] -= num;
          Serial.println(s + " in steps (outside pos) array has been decreased by " + strNum);
          setOutside(i);
          Serial.println("s" + s + " is on.");
        }
        else {
          setOutside(i);
          Serial.println("s" + s + " is on.");
        }
      }
      else if (request.substring(3, 6) == "off") {
        if (request.substring(6, 7) == "+") {
          String strNum = request.substring(7, 8);
          int num = strNum.toInt();
          posInside[i] += num;
          Serial.println(s + " in posInside (inside pos) array has been increased by " + strNum);
          setInside(i);
          Serial.println("s" + s + " is off.");
        }
        else if (request.substring(6, 7) == "-") {
          String strNum = request.substring(7, 8);
          int num = strNum.toInt();
          posInside[i] -= num;
          Serial.println(s + " in posInside (inside pos) array has been decreased by " + strNum);
          setInside(i);
          Serial.println("s" + s + " is off.");
        }
        else {
          setInside(i);
          Serial.println("s" + s + " is off.");
        }
      }
    }
    else if (request.substring(0, 3) == "all") {
      if (request.substring(4, 6) == "on") {
        setAllOutside();
        Serial.println("All servos are in outside positions.");
      }
      else if (request.substring(4, 7) == "off") {
        setAllInside();
        Serial.println("All servos are in inside positions.");
      }
      else Serial.println("Error in 'all' command!");
    } else Serial.println("Error!");
  }
}
