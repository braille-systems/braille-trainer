void setup() {
  Serial.begin(9600);

}

void loop() {
  char c = Serial.read();
  if(c=='w'){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("1");
    } else {
      delay(1000);                       // wait for a second
      Serial.write("1");
      Serial.write(c);
      }
}
