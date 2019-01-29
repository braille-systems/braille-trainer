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

#include <Servo.h>
#include <string.h>

const int n = 6;
const int srvPins[n] = {8, 9, 10, 11, 12};  // servo pins
int posInside[n] = {45, 40, 60, 10, 20, 30};  // "inside" positions
int steps[n] = {90, 80, 70, 60, 50, 40};  // movement from "inside" positions
Servo srv[n];

void setInside(int srvNum) {
  srv[srvNum].attach(srvPins[srvNum]);
  srv[srvNum].write(posInside[srvNum] + steps[srvNum]);
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
  setAllInside();
  Serial.begin(9600);
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
        }
        else if (request.substring(5, 6) == "-") {
          String strNum = request.substring(6, 7);
          int num = strNum.toInt();
          steps[i] -= num;
          Serial.println(s + " in steps (outside pos) array has been decreased by " + strNum);
        }
        else {
          setOutside(i);
          Serial.println(s + " servo is on.");
        }
      }
      else if (request.substring(3, 6) == "off") {
        if (request.substring(6, 7) == "+") {
          String strNum = request.substring(7, 8);
          int num = strNum.toInt();
          posInside[i] += num;
          Serial.println(s + " in posInside (inside pos) array has been increased by " + strNum);
        }
        else if (request.substring(6, 7) == "-") {
          String strNum = request.substring(7, 8);
          int num = strNum.toInt();
          posInside[i] -= num;
          Serial.println(s + " in posInside (inside pos) array has been decreased by " + strNum);
        }
        else {
          setOutside(i);
          Serial.println(s + " servo is off.");
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
