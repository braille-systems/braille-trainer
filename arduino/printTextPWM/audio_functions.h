#ifndef H_AUDIO_FUNCS
#define H_AUDIO_FUNCS

#include"common_declarations.h"

#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_A4  440
#define NOTE_E4  330

#define NOTE_C3  131
#define NOTE_D3  148
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  207

/*
#define NOTE_C3_1  231
#define NOTE_D3_1  248
#define NOTE_E3_1  265
#define NOTE_F3_1  275
#define NOTE_G3_1  296
#define NOTE_A3_1  307
 */
 
const int speaker = 8; //порт к которому подключен динамик
const int muteButton = 10; //порт к которому подключена кнопка джойстика (выведена отдельно)
int muteButtonState;
unsigned long timingSpeak; //тайминг динамика

void alert(int type) {      //сигнал
  int note = 0;
  switch(type) {
    case 'l':
      note = NOTE_B4;
      break;
    case 'r':
      note = NOTE_C4;
      break;
    case 'd':
      note = NOTE_A4;
      break;
    case 'u':
      note = NOTE_E4;
      break;
//    case 1:
//      note = NOTE_C3;
//      break;
//    case '2':
//      note = NOTE_D3;
//      break;
//    case '3':
//      note = NOTE_E3;
//      break;
//    case '4':
//      note = NOTE_F3;
//      break;
//    case '5':
//      note = NOTE_G3;
//      break;
//    case '6':
//      note = NOTE_A3;
//      break;
  }
  tone(speaker, note, 100);
  timingSpeak = millis();
  while(millis() - timingSpeak < 100);
  noTone(speaker);
}

#endif