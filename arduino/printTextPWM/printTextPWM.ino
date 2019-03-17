#include"common_declarations.h"
#include"pwm_functions.h"
#include"audio_functions.h"
#include"keyboard_functions.h"
#include"joystick_functions.h"


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  setAllInside();
  
  pinMode(muteButton, INPUT);
  if(digitalRead(muteButton) == HIGH)
    prevBut = 'm';
  else
    prevBut = 's';
    
  pinMode(speaker, OUTPUT); 
  /*
  //клавиатура
  for (int i = 0; i < m; i++) {
    pinMode(btns[i], INPUT);
    btns_states[i] = true;
  }

  for (int i = 0; i < m; i++) {
    inputStates[i] = false;
  }
  */
}


void loop() {
  //printString("111111");
  //printString("000000");
  buttons();
  joystick();
  if (Serial.available()) {
    String request = Serial.readString();
    
    if (request[0] == '!') {
      isConnected = 1;
    }
    else if(request[0] == '?'){
      reqState = 1;
    }
    else
      printText(request);
  }
 
}
