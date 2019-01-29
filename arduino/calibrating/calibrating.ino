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
}

void loop() {
  char c = Serial.read();
  if (c == 'a') {
    srv[0].attach(srvPins[0]);
    srv[0].write(90);
    Serial.write(c);
  }
  if (c == 'b') {
    srv[0].attach(srvPins[0]);
    srv[0].write(0);
    Serial.write(c);
  }
}
