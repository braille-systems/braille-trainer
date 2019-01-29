/*
   Supported commands:
   - all.off
   - all.on
   - s<number>.off
   - s<number>.on
   - s<number>.off+<digit>
   - s<number>.off-<digit>
   - s<number>.on+<digit>
   - s<number>.on-<digit>
   - p - print two arrays
*/

#include <Servo.h>
#include <string.h>

const int n = 6;
const int srvPins[n] = {8, 9, 10, 11, 12};  // servo pins
const int posInside[n] = {45, 90, 90, 10, 10, 10};  // "inside" positions
const int steps[n] = {90, 90, 90, 90, 90, 90};  // movement from "inside" positions
Servo srv[n];

void setup() {
  for (int i = 0; i < n; i++) {
    srv[i].attach(srvPins[i]);
    srv[i].write(posInside[i]);
    delay(250);
    srv[i].detach();
  }
  Serial.begin(9600);
  Serial.println("Arduino is ready to work.");
}

void loop() {
  if (Serial.available()) {
    String request = Serial.readString();

    /*
     * a function that divides a request string into parts
     */
    
    
    if (request.substring(0, 1) == "p") {
      String pos = "";
      String stp = "";
      
      for (int i = 0; i < n; i++) {
        pos += posInside[i];
        pos += ".";
      }
      
      for (int i = 0; i < n; i++) {
        stp += steps[i];
        stp += ".";
      }
      
      Serial.println(pos);
      Serial.println(stp);
    }    
  }
}
