//We always have to include the library
#include "LedControlMS.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include <Keypad.h>
/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
const byte ROWS = 4; //four rows
const byte COLS = 2; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {1,4},
  {2,5},
  {3,6},
  {7,8}
};
byte rowPins[ROWS] = {5,4,3,2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7,6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LedControl lc = LedControl(12, 10, 11, 1);

int mode;
bool flag1;
bool flag2;

#define enter 8

const byte IMG_OK[8] = {
  B01111110,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B01111110
};

const byte IMG_NO[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};
const byte A[8] = {
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B01111110,
  B01000010,
  B01000010,
  B01000010
};
const byte B[8] =
{
  B01111100,
  B01000000,
  B01000000,
  B01111100,
  B01000010,
  B01000010,
  B01000010,
  B01111100,
};
const byte V[8] =
{
  B01111000,
  B01000100,
  B01000100,
  B01111100,
  B01000010,
  B01000010,
  B01000010,
  B01111100,
};
const byte G[8] =
{
  B01111110,
  B01000010,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
};
const byte D[8] =
{
  B00011000,
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B01111110,
  B01000010,
};
const byte E[8] =
{
  B01111110,
  B01000000,
  B01000000,
  B01111100,
  B01111100,
  B01000000,
  B01000000,
  B01111110,
};
const byte YO[8] =
{
  B00101000,
  B01111100,
  B01000000,
  B01000000,
  B01111100,
  B01000000,
  B01000000,
  B01111100,
};

const  byte J[8] =
{
  B10000001,
  B10011001,
  B10011001,
  B11111111,
  B11111111,
  B10011001,
  B10011001,
  B10000001,
};

const byte Z[8] =
{
  B00111100,
  B00000010,
  B00000010,
  B00011100,
  B00000010,
  B00000010,
  B00000010,
  B00111100,
};

const byte I[8] =
{
  B01000010,
  B01000010,
  B01000110,
  B01001010,
  B01010010,
  B01100010,
  B01000010,
  B01000010,
};

const byte IY[8] =
{
  B00011000,
  B00000000,
  B01000010,
  B01000110,
  B01001010,
  B01010010,
  B01100010,
  B01000010,
};

const byte K [8] =
{
  B01000100,
  B01001000,
  B01010000,
  B01100000,
  B01010000,
  B01001000,
  B01000100,
  B01000010,
};

const byte L[8] =
{
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
};
const byte M[8] =
{
  B00000000,
  B10000010,
  B11000110,
  B10101010,
  B10010010,
  B10000010,
  B10000010,
  B10000010,
};

const byte N[8] =
{
  B00000000,
  B01000010,
  B01000010,
  B01000010,
  B01111110,
  B01000010,
  B01000010,
  B01000010,
};

const byte O[8] =
{
  B00111000,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B00111000,
};
const byte P[8] =
{
  B01111110,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
};
const byte R[8] =
{
  B01111000,
  B01000100,
  B01000100,
  B01111000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
};
const byte S[8] =
{
  B00111100,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00111100
};
const byte T[8] =
{
  B11111111,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
};
const byte U[8] =
{
  B00100010,
  B00100010,
  B00100010,
  B00011110,
  B00000010,
  B00000010,
  B00000010,
  B00111100,
};
const byte F[8] =
{
  B11111110,
  B10010010,
  B10010010,
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
};
const byte X[8] =
{
  B00000000,
  B10000010,
  B01000100,
  B00101000,
  B00010000,
  B00101000,
  B01000100,
  B10000010,
};
const byte CE[8] =
{
  B10000010,
  B10000010,
  B10000010,
  B10000010,
  B10000010,
  B10000010,
  B11111110,
  B00000011,
};
const byte C[8] =
{
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B00111100,
  B00000100,
  B00000100,
  B00000100,
};
const byte SH[8] =
{
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
};
const byte SHA[8] =
{
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B10010010,
  B10010010,
  B11111111,
  B00000001,
};
const byte HARD[8] =
{
  B00000000,
  B01100000,
  B00100000,
  B00100000,
  B00111100,
  B00100010,
  B00100010,
  B00111100,
};
const byte YI[8] =
{
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111001,
  B10000101,
  B10000101,
  B11111001,
};
const byte SOFT[8] =
{
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01111000,
  B01000100,
  B01000100,
  B01111000,
};
const byte EE[8] =
{
  B01111000,
  B00000100,
  B00000010,
  B00111110,
  B00111110,
  B00000010,
  B00000100,
  B01111000,
};
const byte YOU[8] =
{
  B10001110,
  B10010001,
  B10010001,
  B11110001,
  B11110001,
  B10010001,
  B10010001,
  B10001110,
};
const byte YA[8] =
{
  B00111100,
  B01000100,
  B01000100,
  B00111100,
  B00001100,
  B00010100,
  B00100100,
  B01000100,
};
const byte WAR[8] =
{
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00011000,
};
const byte QU[8] =
{
  B00011000,
  B00100100,
  B00000100,
  B00001000,
  B00010000,
  B00010000,
  B00000000,
  B00010000,
};
const byte DOT[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
};
const byte SPACE[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00000000,
};
const byte MINUS[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
};
const byte PLUS[8] =
{
  B00011000,
  B00011000,
  B00011000,
  B11111111,
  B11111111,
  B00011000,
  B00011000,
  B00011000,
};
const byte ZAP[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00001000,
  B00010000,
};
const byte TWODOTS[8] =
{
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
};
const byte DOTZAP[8] =
{
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00011000,
  B00001000,
  B00010000,
};
const byte NUM_ZERO[8] =
{ B00111100,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B00111100
};
const byte NUM_ONE[8] =
{ B00001000,
  B00011000,
  B00101000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00111100
};
const byte NUM_TWO[8] =
{ B00111100,
  B01000010,
  B01000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110
};
const byte NUM_THI[8] =
{ B00111100,
  B01000010,
  B00000010,
  B00011100,
  B00000010,
  B00000010,
  B01000010,
  B00111100
};
const byte NUM_FO[8] =
{ B01000100,
  B01000100,
  B01000100,
  B01000100,
  B00111110,
  B00000100,
  B00000100,
  B00000100
};
const byte NUM_FIVE[8] =
{ B00111100,
  B00100000,
  B00100000,
  B00111000,
  B00000100,
  B00000100,
  B00100100,
  B00011000
};
const byte NUM_SIX[8] =
{ B00011000,
  B00100100,
  B00100000,
  B00111000,
  B00100100,
  B00100100,
  B00100100,
  B00011000
};
const byte NUM_SEVEN[8] =
{ B01111111,
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000
};
const byte NUM_AIT[8] =
{ B00011000,
  B00100100,
  B00100100,
  B00011000,
  B00100100,
  B00100100,
  B00100100,
  B00011000
};
const byte NUM_NINE[8] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011110,
  B00000010,
  B00100010,
  B00011100
};

const bool A_Brail[8] = {true, false, false, false, false, false, false, false};
const bool B_Brail[8] = {true, true, false, false, false, false, false, false};
const bool V_Brail[8] = {false, true, false, true, true, true, false, false};
const bool G_Brail[8] = {true, true, false, true, true, false, false, false};
const bool D_Brail[8] = {true, false, false, true, true, false, false, false};
const bool E_Brail[8] = {true, false, false, false, true, false, false, false};
const bool YO_Brail[8] = {true, false, false, false, false, true, false, false};
const bool J_Brail[8] = {false, true, false, true, true, false, false, false};
const bool Z_Brail[8] = {true, false, true, false, true, true, false, false};
const bool I_Brail[8] = {false, true, false, true, false, false, false, false};
const bool IY_Brail[8] = {true, true, true, true, false, true, false, false};
const bool K_Brail[8] = {true, false, true, false, false, false, false, false};
const bool L_Brail[8] = {true, true, true, false, false, false, false, false};
const bool M_Brail[8] = {true, false, true, true, false, false, false, false};
const bool N_Brail[8] = {true, false, true, true, true, false, false, false};
const bool O_Brail[8] = {true, false, true, false, true, false, false, false};
const bool P_Brail[8] = {true, true, true, true, false, false, false, false};
const bool R_Brail[8] = {true, true, true, false, true, false, false, false};
const bool S_Brail[8] = {false, true, true, true, false, false, false, false};
const bool T_Brail[8] = {false, true, true, true, true, false, false, false};
const bool U_Brail[8] = {true, false, true, false, false, true, false, false};
const bool F_Brail[8] = {true, true, false, true, false, false, false, false};
const bool X_Brail[8] = {true, true, false, false, true, false, false, false};
const bool CE_Brail[8] = {true, false, false, true, false, false, false, false};
const bool C_Brail[8] = {true, true, true, true, true, false, false, false};
const bool SH_Brail[8] = {true, false, false, false, true, true, false, false};
const bool SHA_Brail[8] = {true, false, true, true, false, true, false, false};
const bool HARD_Brail[8] = {true, true, true, false, true, true, false, false};
const bool YI_Brail[8] = {false, true, true, true, false, true, false, false};
const bool SOFT_Brail[8] = {false, true, true, true, true, true, false, false};
const bool EE_Brail[8] = {false, true, false, true, false, true, false, false};
const bool YOU_Brail[8] = {true, true, false, false, true, true, false, false};
const bool YA_Brail[8] = {true, true, false, true, false, true, false, false};
//ZNAKI
const bool EMPTY_Brail[8] = {false, false, false, false, false, false, false, false};
const bool WAR_Brail[8] = {false, true, true, false, true, false, false, false};
const bool QU_Brail[8] = {false, true, false, false, false, true, false, false};
const bool DOT_Brail[8] = {false, true, false, false, true, true, false, false};
const bool SPASE_Brail[8] = {false, false, true, false, false, true, false, false};
const bool MINUS_Brail[8] = {false, false, true, false, false, true, false, false};
const bool PLUS_Brail[8] = {false, true, true, false, true, false, false, false};
const bool ZAP_Brail[8] = {false, true, false, false, false, false, false, false};
const bool TWODOTS_Brail[8] = {false, true, false, false, true, false, false, false};
const bool DOTZAP_Brail[8] = {false, true, true, false, false, false, false, false};
//NUMBERS
const bool NUM_Brail[8] = {false, false, true, true, true, true, false, false};
const bool NUM_ZERO_Brail[8] = {false, true, false, true, true, false, false, false};
const bool NUM_ONE_Brail[8] = {true, false, false, false, false, false, false, false};
const bool NUM_TWO_Brail[8] = {true, true, false, false, false, false, false, false};
const bool NUM_THI_Brail[8] = {true, false, false, true, false, false, false, false};
const bool NUM_FO_Brail[8] = {true, false, false, true, true, false, false, false};
const bool NUM_FIVE_Brail[8] = {true, false, false, false, true, false, false, false};
const bool NUM_SIX_Brail[8] = {true, true, false, true, false, false, false, false};
const bool NUM_SEVEN_Brail[8] = {true, true, false, true, true, false, false, false};
const bool NUM_AIT_Brail[8] = {true, true, false, false, true, false, false, false};
const bool NUM_NINE_Brail[8] = {false, true, false, true, false, false, false, false};
const int SERVO_POSITIONS[4] = {300, 360, 140, 450};
//300 -
byte DatasBuffer[8];
byte BUTTON_STATE[11];
bool BUTTON_SWICH[8];
bool BUTTON_LASTSWICH[8];
byte state = 0;
byte menu = 0;
byte c[8];
byte azbuka = 1;
byte CurBukva = 0;
unsigned long previousMillis = 0;
unsigned long previousMillisButtons = 0;
unsigned long previousMillisState = 0;
long interval = 20;
int i;


#define enter 8


void setup() {
  pinMode(enter, INPUT_PULLUP);
  lc.shutdown(0, false); // Wake up displays
  lc.shutdown(1, false);
  lc.setIntensity(0, 5); // Set intensity levels
  lc.setIntensity(1, 5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);

  Serial.begin(9600);
  mp3_set_serial (Serial);
  mp3_set_volume (27);

  pwm.begin();
  pwm.setPWMFreq(60);
  yield();
  mode = 1;
  flag1;
  flag2;

  randomSeed(analogRead(A0));
  analogWrite(A3, INPUT_PULLUP);
  analogWrite(A2, INPUT_PULLUP);
  
 // CheakMenu();
 //  setMatrix(NUM_ONE);
}


/*
  if (millis() - previousMillisButtons >= interval) {
    interval = 20;
    BUTTON_STATE[0] = digitalRead(BUT1);
    BUTTON_STATE[1] = digitalRead(BUT2);
    BUTTON_STATE[2] = digitalRead(BUT3);
    BUTTON_STATE[3] = digitalRead(BUT4);
    BUTTON_STATE[4] = digitalRead(BUT5);
    BUTTON_STATE[5] = digitalRead(BUT6);
    BUTTON_STATE[6] = digitalRead(BUT7);
    BUTTON_STATE[7] = digitalRead(BUT8);
    BUTTON_STATE[8] = digitalRead(BUT9);//UP
    BUTTON_STATE[9] = digitalRead(BUT10);//DOWN
    BUTTON_STATE[10] = digitalRead(BUT11);//ENTER
    previousMillisButtons = millis();
  }
  if (BUTTON_STATE[8] == LOW) {
    if (menu != 2) {
      menu++;
      CheakMenu();
    }
  }
  if (BUTTON_STATE[9] == LOW) {
    if (menu != 0) {
      menu--;
      CheakMenu();
    }
  }
  if (menu == 2) {//Тест
    if (state == 0) {
      if (BUTTON_STATE[10] == LOW) {
        CurBukva = random(0, 34);
        state = 1;
        previousMillis = millis();
        VoiseAndPrint(CurBukva);
        delay(2000);
        lc.clearDisplay(0);
        return;
      }
    }
    if (state == 1) {
      PrintToMatrix();
      if (BUTTON_STATE[10] == LOW) {
        chakBukvaAndMatrix(CurBukva);
        delay(1000);
        state = 0;
        for (byte k = 0 ; k < 8; k++) {
          BUTTON_SWICH[k] = false;
        }
        return;
      }
      for (byte i = 0 ; i < 8; i++) {
        if ( BUTTON_STATE[i] == LOW) {
          if (BUTTON_STATE[i] != BUTTON_LASTSWICH[i]) {
            BUTTON_SWICH[i] = !BUTTON_SWICH[i];
            if (BUTTON_SWICH[i] == HIGH) {
              mp3_play (42);
            } else {
              mp3_play (43);
            }
          }
        }
        BUTTON_LASTSWICH[i] = BUTTON_STATE[i];
      }
    }
  }
  else if (menu == 1) {//Азбука
    
  }
  else if (menu == 0) {//Справочник
    if (state == 0) {
      PrintToMatrix();
      if (BUTTON_STATE[10] == LOW) {
        byte Datas[8] = {BUTTON_SWICH[0], BUTTON_SWICH[1], BUTTON_SWICH[2], BUTTON_SWICH[3], BUTTON_SWICH[4], BUTTON_SWICH[5], BUTTON_SWICH[6], BUTTON_SWICH[7]};
        lc.clearDisplay(0);
        if (GetBrailFromPixels(Datas) == 50) {
          state = 2;
          mp3_play (53); //Введите букву
          ClearBrailPanel();
        } else if (GetBrailFromPixels(Datas) < 50) {
          VoiseAndPrint(GetBrailFromPixels(Datas));
          SetServo(Datas);
          ClearBrailPanel();
          state = 1;
        }
        previousMillis = millis();
        delay(2000);
        lc.clearDisplay(0);
        return;
      }
      for (byte i = 0 ; i < 8; i++) {
        if ( BUTTON_STATE[i] == LOW) {
          if (BUTTON_STATE[i] != BUTTON_LASTSWICH[i]) {
            BUTTON_SWICH[i] = !BUTTON_SWICH[i];
            if (BUTTON_SWICH[i] == HIGH)
              mp3_play (42);
            else
              mp3_play (43);
          }
        }
        BUTTON_LASTSWICH[i] = BUTTON_STATE[i];
      }
    }
    if (state == 1 && millis() - previousMillis >= interval * 10) {
      for (byte i = 0 ; i < 8; i++) {
        if ( BUTTON_STATE[i] == LOW) {
          for (byte k = 0 ; k < 8; k++)
            BUTTON_SWICH[k] = false;
          state = 0;
          lc.clearDisplay(0);
        }
      }
    }
    if (state == 2) {
      PrintToMatrix();
      if (BUTTON_STATE[10] == LOW) {
        byte Datas[8] = {BUTTON_SWICH[0], BUTTON_SWICH[1], BUTTON_SWICH[2], BUTTON_SWICH[3], BUTTON_SWICH[4], BUTTON_SWICH[5], BUTTON_SWICH[6], BUTTON_SWICH[7]};
        lc.clearDisplay(0);
        VoiseAndPrint(GetBrailNumberFromPixels(Datas));
        SetServo(Datas);
        state = 1;
        previousMillis = millis();
        delay(2200);
        lc.clearDisplay(0);
        return;
      }
      for (byte i = 0 ; i < 8; i++) {
        if ( BUTTON_STATE[i] == LOW) {
          if (BUTTON_STATE[i] != BUTTON_LASTSWICH[i]) {
            BUTTON_SWICH[i] = !BUTTON_SWICH[i];
            if (BUTTON_SWICH[i] == HIGH)
              mp3_play (42);
            else
              mp3_play (43);
          }
        }
        BUTTON_LASTSWICH[i] = BUTTON_STATE[i];
      }
    }
  }
 */



void ClearBrailPanel() {
  for (byte k = 0 ; k < 8; k++)
    BUTTON_SWICH[k] = false;
}
void ClearButtonState() {
  for (byte k = 0 ; k < 8; k++)
    BUTTON_STATE[k] = 0;
}
void ResetAll() {
  state = 0;
  azbuka = 0;
  lc.clearDisplay(0);
  ClearBrailPanel();
  previousMillis = millis();
  ClearButtonState();
}

void CheakMenu() {
  if (mode == 2)//РЕЖИМ ТЕСТ
    mp3_play (39);
  else if (mode == 0)//РЕЖИМ СПРАВОЧНИК
    mp3_play (37);
  else if (mode == 1)//РЕЖИМ АЗБУКА
    mp3_play (38);
  ResetAll();
  delay(1000);
}

void PrintToMatrix() {
  for (byte i = 0 ; i < 8; i++) {
    lc.setLed(0, i / 2 + 2, i % 2 + 3,  BUTTON_SWICH[i]);
  }
}
void setMatrix(const byte c[8]) {
  for (byte i = 0; i < 8; i++) {
    lc.setRow(0, i, c[i]);
  }
}
void setMatrixBrail(const bool c[8]) {
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2 + 2, i % 2 + 3, c[i]);
}
void setTextBrail(const bool C1[8], const bool C2[8], const bool C3[8], const bool C4[8], const bool C5[8], const bool C6[8] ) {
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2, i % 2, C1[i]);
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2, i % 2 + 3, C2[i]);
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2, i % 2 + 6, C3[i]);
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2 + 5, i % 2, C4[i]);
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2 + 5, i % 2 + 3, C5[i]);
  for (byte i = 0 ; i < 8; i++)
    lc.setLed(0, i / 2 + 5, i % 2 + 6, C6[i]);
}
void SetServo( byte Data[8]) {
  //0
  if (Data[0] == true && Data[3] == true) {
    pwm.setPWM(0, 0, 140);
  } else if (Data[0] == true && Data[3] == false) {
    pwm.setPWM(0, 0, 360);
  } else if (Data[0] == false && Data[3] == true) {
    pwm.setPWM(0, 0, 590);
  } else if (Data[0] == false && Data[3] == false) {
    pwm.setPWM(0, 0, 450);
  }
  //1
  delay(250);
  if (Data[1] == true && Data[4] == true) {
    pwm.setPWM(1, 0, 150);
  } else if (Data[1] == true && Data[4] == false) {
    pwm.setPWM(1, 0, 340);
  } else if (Data[1] == false && Data[4] == true) {
    pwm.setPWM(1, 0, 560);
  } else if (Data[1] == false && Data[4] == false) {
    pwm.setPWM(1, 0, 420);
  }
  //2
  delay(250);
  if (Data[2] == true && Data[5] == true) {
    pwm.setPWM(2, 0, 550);
  } else if (Data[2] == true && Data[5] == false) {
    pwm.setPWM(2, 0, 310);
  } else if (Data[2] == false && Data[5] == true) {
    pwm.setPWM(2, 0, 150);
  } else if (Data[2] == false && Data[5] == false) {
    pwm.setPWM(2, 0, 225);
  }
  //3
  delay(250);
  if (Data[6] == true && Data[7] == true) {
    pwm.setPWM(3, 0, 530);
  } else if (Data[6] == true && Data[7] == false) {
    pwm.setPWM(3, 0, 300);
  } else if (Data[6] == false && Data[7] == true) {
    pwm.setPWM(3, 0, 150);
  } else if (Data[6] == false && Data[7] == false) {
    pwm.setPWM(3, 0, 225);
  }
  delay(250);
}
byte GetBrailNumberFromPixels( byte Data[8]) {
  byte sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_ZERO_Brail[i]) sov++; if (sov == 8) return 51; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_ONE_Brail[i]) sov++; if (sov == 8) return 52; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_TWO_Brail[i]) sov++; if (sov == 8) return 53; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_THI_Brail[i]) sov++; if (sov == 8) return 54; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_FO_Brail[i]) sov++; if (sov == 8) return 55; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_FIVE_Brail[i]) sov++; if (sov == 8) return 56; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_SIX_Brail[i]) sov++; if (sov == 8) return 57; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_SEVEN_Brail[i]) sov++; if (sov == 8) return 58; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_AIT_Brail[i]) sov++; if (sov == 8) return 59; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_NINE_Brail[i]) sov++; if (sov == 8) return 60; sov = 0;
  return 255;
}
byte GetBrailFromPixels( byte Data[8]) {
  byte sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == A_Brail[i]) sov++; if (sov == 8) return 1; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == B_Brail[i]) sov++; if (sov == 8) return 2; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == V_Brail[i]) sov++; if (sov == 8) return 3; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == G_Brail[i]) sov++; if (sov == 8) return 4; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == D_Brail[i]) sov++; if (sov == 8) return 5; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == E_Brail[i]) sov++; if (sov == 8) return 6; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == YO_Brail[i]) sov++; if (sov == 8) return 7; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == J_Brail[i]) sov++; if (sov == 8) return 8; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == Z_Brail[i]) sov++; if (sov == 8) return 9; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == I_Brail[i]) sov++; if (sov == 8) return 10; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == IY_Brail[i]) sov++; if (sov == 8) return 11; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == K_Brail[i]) sov++; if (sov == 8) return 12; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == L_Brail[i]) sov++; if (sov == 8) return 13; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == M_Brail[i]) sov++; if (sov == 8) return 14; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == N_Brail[i]) sov++; if (sov == 8) return 15; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == O_Brail[i]) sov++; if (sov == 8) return 16; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == P_Brail[i]) sov++; if (sov == 8) return 17; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == R_Brail[i]) sov++; if (sov == 8) return 18; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == S_Brail[i]) sov++; if (sov == 8) return 19; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == T_Brail[i]) sov++; if (sov == 8) return 20; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == U_Brail[i]) sov++; if (sov == 8) return 21; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == F_Brail[i]) sov++; if (sov == 8) return 22; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == X_Brail[i]) sov++; if (sov == 8) return 23; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == CE_Brail[i]) sov++; if (sov == 8) return 24; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == C_Brail[i]) sov++; if (sov == 8) return 25; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == SH_Brail[i]) sov++; if (sov == 8) return 26; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == SHA_Brail[i]) sov++; if (sov == 8) return 27; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == HARD_Brail[i]) sov++; if (sov == 8) return 28; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == YI_Brail[i]) sov++; if (sov == 8) return 29; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == SOFT_Brail[i]) sov++; if (sov == 8) return 30; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == EE_Brail[i]) sov++; if (sov == 8) return 31; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == YOU_Brail[i]) sov++; if (sov == 8) return 32; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == YA_Brail[i]) sov++; if (sov == 8) return 33; sov = 0;
  //ZNAKI
  for (byte i = 0; i < 8; i++) if (Data[i] == WAR_Brail[i]) sov++; if (sov == 8) return 34; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == QU_Brail[i]) sov++; if (sov == 8) return 35; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == DOT_Brail[i]) sov++; if (sov == 8) return 36; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == SPASE_Brail[i]) sov++; if (sov == 8) return 37; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == MINUS_Brail[i]) sov++; if (sov == 8) return 38; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == PLUS_Brail[i]) sov++; if (sov == 8) return 39; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == ZAP_Brail[i]) sov++; if (sov == 8) return 40; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == TWODOTS_Brail[i]) sov++; if (sov == 8) return 41; sov = 0;
  for (byte i = 0; i < 8; i++) if (Data[i] == DOTZAP_Brail[i]) sov++; if (sov == 8) return 42; sov = 0;
  //NUMBERS
  for (byte i = 0; i < 8; i++) if (Data[i] == NUM_Brail[i]) sov++; if (sov == 8) return 50; sov = 0;
  ClearBrailPanel();
  mp3_play (98);
  return 255;
}
void AlphavitToServo(byte bukva) {
  //DatasBuffer
  switch (bukva) {
    case 1:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = A_Brail[i];
      break;
    case 2:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = B_Brail[i];
      break;
    case 3:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = V_Brail[i];
      break;
    case 4:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = G_Brail[i];
      break;
    case 5:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = D_Brail[i];
      break;
    case 6:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = E_Brail[i];
      break;
    case 7:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = YO_Brail[i];
      break;
    case 8:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = J_Brail[i];
      break;
    case 9:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = Z_Brail[i];
      break;
    case 10:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = I_Brail[i];
      break;
    case 11:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = IY_Brail[i];
      break;
    case 12:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = K_Brail[i];
      break;
    case 13:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = L_Brail[i];
      break;
    case 14:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = M_Brail[i];
      break;
    case 15:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = N_Brail[i];
      break;
    case 16:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = O_Brail[i];
      break;
    case 17:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = P_Brail[i];
      break;
    case 18:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = R_Brail[i];
      break;
    case 19:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = S_Brail[i];
      break;
    case 20:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = T_Brail[i];
      break;
    case 21:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = U_Brail[i];
      break;
    case 22:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = F_Brail[i];
      break;
    case 23:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = X_Brail[i];
      break;
    case 24:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = CE_Brail[i];
      break;
    case 25:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = C_Brail[i];
      break;
    case 26:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = SH_Brail[i];
      break;
    case 27:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = SHA_Brail[i];
      break;
    case 28:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = HARD_Brail[i];
      break;
    case 29:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = YI_Brail[i];
      break;
    case 30:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = SOFT_Brail[i];
      break;
    case 31:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = EE_Brail[i];
      break;
    case 32:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = YOU_Brail[i];
      break;
    case 33:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = YA_Brail[i];
      break;
    case 34:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = WAR_Brail[i];
      break;
    case 35:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = QU_Brail[i];
      break;
    case 36:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = DOT_Brail[i];
      break;
    case 37:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = SPASE_Brail[i];
      break;
    case 38:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = MINUS_Brail[i];
      break;
    case 39:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = PLUS_Brail[i];
      break;
    case 40:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = ZAP_Brail[i];
      break;
    case 41:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = TWODOTS_Brail[i];
      break;
    case 42:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = DOTZAP_Brail[i];
      break;
    case 51:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_ZERO_Brail[i];
      break;
    case 52:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_ONE_Brail[i];
      break;
    case 53:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_TWO_Brail[i];
      break;
    case 54:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_THI_Brail[i];
      break;
    case 55:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_FO_Brail[i];
      break;
    case 56:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_FIVE_Brail[i];
      break;
    case 57:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_SIX_Brail[i];
      break;
    case 58:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_SEVEN_Brail[i];
      break;
    case 59:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_AIT_Brail[i];
      break;
    case 60:
      for (byte i = 0 ; i < 8; i++) DatasBuffer[i] = NUM_NINE_Brail[i];
      break;
  }
}
void VoiseAndPrint(byte priem) {
    switch (priem) {
    case 1:
      setMatrix(A);
      mp3_play (1);
      break;
    case 2:
      setMatrix(B);
      mp3_play (2);
      break;
    case 3:
      setMatrix(V);
      mp3_play (3);
      break;
    case 4:
      setMatrix(G);
      mp3_play (4);
      break;
    case 5:
      setMatrix(D);
      mp3_play (5);
      break;
    case 6:
      setMatrix(E);
      mp3_play (6);
      break;
    case 7:
      setMatrix(YO);
      mp3_play (7);
      break;
    case 8:
      setMatrix(J);
      mp3_play (8);
      break;
    case 9:
      setMatrix(Z);
      mp3_play (9);
      break;
    case 10:
      setMatrix(I);
      mp3_play (10);
      break;
    case 11:
      setMatrix(IY);
      mp3_play (11);
      break;
    case 12:
      setMatrix(K);
      mp3_play (12);
      break;
    case 13:
      setMatrix(L);
      mp3_play (13);
      break;
    case 14:
      setMatrix(M);
      mp3_play (14);
      break;
    case 15:
      setMatrix(N);
      mp3_play (15);
      break;
    case 16:
      setMatrix(O);
      mp3_play (16);
      break;
    case 17:
      setMatrix(P);
      mp3_play (17);
      break;
    case 18:
      setMatrix(R);
      mp3_play (18);
      break;
    case 19:
      setMatrix(S);
      mp3_play (19);
      break;
    case 20:
      setMatrix(T);
      mp3_play (20);
      break;
    case 21:
      setMatrix(U);
      mp3_play (21);
      break;
    case 22:
      setMatrix(F);
      mp3_play (22);
      break;
    case 23:
      setMatrix(X);
      mp3_play (23);
      break;
    case 24:
      setMatrix(CE);
      mp3_play (24);
      break;
    case 25:
      setMatrix(C);
      mp3_play (25);
      break;
    case 26:
      setMatrix(SH);
      mp3_play (26);
      break;
    case 27:
      setMatrix(SHA);
      mp3_play (27);
      break;
    case 28:
      setMatrix(HARD);
      mp3_play (28);
      break;
    case 29:
      setMatrix(YI);
      mp3_play (30);
      break;
    case 30:
      setMatrix(SOFT);
      mp3_play (29);
      break;
    case 31:
      setMatrix(EE);
      mp3_play (31);
      break;
    case 32:
      setMatrix(YOU);
      mp3_play (32);
      break;
    case 33:
      setMatrix(YA);
      mp3_play (33);
      break;
    case 34:
      setMatrix(WAR);
      mp3_play (44);
      break;
    case 35:
      setMatrix(QU);
      mp3_play (45);
      break;
    case 36:
      setMatrix(DOT);
      mp3_play (46);
      break;
    case 37:
      setMatrix(SPACE);
      mp3_play (47);
      break;
    case 38:
      setMatrix(MINUS);
      mp3_play (48);
      break;
    case 39:
      setMatrix(PLUS);
      mp3_play (49);
      break;
    case 40:
      setMatrix(ZAP);
      mp3_play (50);
      break;
    case 41:
      setMatrix(TWODOTS);
      mp3_play (51);
      break;
    case 42:
      setMatrix(DOTZAP);
      mp3_play (52);
      break;
    case 51:
      setMatrix(NUM_ZERO);
      mp3_play (61);
      break;
    case 52:
      setMatrix(NUM_ONE);
      mp3_play (62);
      break;
    case 53:
      setMatrix(NUM_TWO);
      mp3_play (63);
      break;
    case 54:
      setMatrix(NUM_THI);
      mp3_play (64);
      break;
    case 55:
      setMatrix(NUM_FO);
      mp3_play (65);
      break;
    case 56:
      setMatrix(NUM_FIVE);
      mp3_play (66);
      break;
    case 57:
      setMatrix(NUM_SIX);
      mp3_play (67);
      break;
    case 58:
      setMatrix(NUM_SEVEN);
      mp3_play (68);
      break;
    case 59:
      setMatrix(NUM_AIT);
      mp3_play (69);
      break;
    case 60:
      setMatrix(NUM_NINE);
      mp3_play (70);
      break;
    default:
      ClearBrailPanel();
      mp3_play (98);
      break;
  }
}
void chakBukvaAndMatrix(byte num) {
  byte Datas[8] = {BUTTON_SWICH[0], BUTTON_SWICH[1], BUTTON_SWICH[2], BUTTON_SWICH[3], BUTTON_SWICH[4], BUTTON_SWICH[5], BUTTON_SWICH[6], BUTTON_SWICH[7]};
  lc.clearDisplay(0);
  if ( GetBrailFromPixels(Datas) == num) {
    mp3_play (41);
    setMatrix(IMG_OK);
    SetServo(Datas);
    delay(2000);
    lc.clearDisplay(0);
    return true;
  }
  mp3_play (40);
  setMatrix(IMG_NO);
  AlphavitToServo(CurBukva);
  SetServo(DatasBuffer);
  // SetServo(Datas);
  delay(2000);
  lc.clearDisplay(0);
  return false;
}

void mode1(){ //РЕЖИМ АЗБУКА
    interval = 400;
    if (millis() - previousMillis >= interval) {
      previousMillis = millis();
      if (analogRead(A3) > 100) {//Next
        
        if (azbuka != 60) {
          if (azbuka != 42) {
            azbuka++;
          } else
            azbuka = 51;
        } else {
          azbuka = 1;          
        }
       
        AlphavitToServo(azbuka);
        SetServo(DatasBuffer);
        VoiseAndPrint(azbuka);
      }
      if (analogRead(A3) == 0) {//Prev
        if(azbuka == 51){
          azbuka = 42;
          
          AlphavitToServo(azbuka);
          SetServo(DatasBuffer);
          VoiseAndPrint(azbuka);
        }
        if (azbuka != 1) {
          azbuka--;
          AlphavitToServo(azbuka);
          SetServo(DatasBuffer);
           VoiseAndPrint(azbuka);
        }
        
      }
    }
  }

  void mode2()//РЕЖИМ ТЕСТ
  {
  if (state == 0) {
     if (state == 0) {
      CurBukva = random(0, 34);
      state = 1;
      previousMillis = millis();
      VoiseAndPrint(CurBukva);
      delay(1500);
      lc.clearDisplay(0);
      return;
      }
    }
  if (state == 1 && millis() - previousMillis >= interval * 10) {
      int customKey = customKeypad.getKey();
      if (customKey){BUTTON_STATE[customKey-1]=1;}    
      if (digitalRead(enter)==LOW){Serial.println("flag");
      if (GetBrailFromPixels(BUTTON_STATE)==CurBukva){setMatrix(IMG_OK); SetServo(BUTTON_STATE) ;mp3_play (41);} 
      else {setMatrix(IMG_NO); AlphavitToServo(CurBukva); SetServo(DatasBuffer);mp3_play (40); };
      delay(2000); ResetAll();};
    }  
  }
  void mode3()//РЕЖИМ СПРАВОЧНИК
  {
    int customKey = customKeypad.getKey();
if (customKey){BUTTON_STATE[customKey-1]=1;
Serial.print(BUTTON_STATE[0]);Serial.print(BUTTON_STATE[1]);Serial.print(BUTTON_STATE[2]);Serial.print(BUTTON_STATE[3]);Serial.print(BUTTON_STATE[4]);Serial.print(BUTTON_STATE[5]);Serial.print(BUTTON_STATE[6]);Serial.println(BUTTON_STATE[7]);};
if (digitalRead(enter)==LOW){VoiseAndPrint(GetBrailFromPixels(BUTTON_STATE));delay(1000); ResetAll();};

    }

void loop() {
  interval = 1000;
  //Serial.println(mode);
    if (millis() - previousMillisState >= interval) {
      previousMillisState = millis();
      if (analogRead(A2) == 0) {//Next
        mode++; if (mode>3){mode=1;};CheakMenu(); delay(500);
        Serial.println(mode);
      }
      if (analogRead(A2) > 100) {//Prev
        mode--; if (mode<1){mode=3;};CheakMenu(); delay(500);
        Serial.println(mode);
      }
    }
  
 /* switch (mode)
  {
    case 1: mode1(); break;
    case 2: mode2(); break;
    case 3: mode3(); break;
  }*/
  
  if (mode == 1) { 
    Serial.println(mode);
    interval = 300;
    if (millis() - previousMillis >= interval) {
      previousMillis = millis();
      if (analogRead(A3) > 100) {//Next
        
        Serial.println("flag");
        if (azbuka != 60) {
          if (azbuka != 42) {
            azbuka++;
          } else
            azbuka = 51;
        } else {
          azbuka = 1;          
        }
       
        AlphavitToServo(azbuka);
        SetServo(DatasBuffer);
        VoiseAndPrint(azbuka);
        
      }
      if (analogRead(A3) == 0) {//Prev
        
        if(azbuka == 51){
          azbuka = 42;
          
          AlphavitToServo(azbuka);
          SetServo(DatasBuffer);
          delay(50);
          VoiseAndPrint(azbuka);
          delay(100);
        }
        if (azbuka != 1) {
          azbuka--;
          AlphavitToServo(azbuka);
          SetServo(DatasBuffer);
          delay(50);
           VoiseAndPrint(azbuka);
           delay(100);
        }
        
        }}}
    
    if (mode == 2) {
      if (state == 0) {
     if (state == 0) {
      CurBukva = random(0, 34);
      state = 1;
      previousMillis = millis();
      VoiseAndPrint(CurBukva);
      delay(1500);
      lc.clearDisplay(0);
      return;
      }
    }
  if (state == 1) {
      int customKey = customKeypad.getKey();
      if (customKey){BUTTON_STATE[customKey-1]=1;}    
      if (digitalRead(enter)==LOW){Serial.println("flag");
      if (GetBrailFromPixels(BUTTON_STATE)==CurBukva){setMatrix(IMG_OK); SetServo(BUTTON_STATE) ;mp3_play (41);} 
      else {setMatrix(IMG_NO); AlphavitToServo(CurBukva); SetServo(DatasBuffer);mp3_play (40); };
      delay(2000); ResetAll();};
    }  
      }

    if (mode == 3) {
       int customKey = customKeypad.getKey();
if (customKey){BUTTON_STATE[customKey-1]=1;
Serial.print(BUTTON_STATE[0]);Serial.print(BUTTON_STATE[1]);Serial.print(BUTTON_STATE[2]);Serial.print(BUTTON_STATE[3]);Serial.print(BUTTON_STATE[4]);Serial.print(BUTTON_STATE[5]);Serial.print(BUTTON_STATE[6]);Serial.println(BUTTON_STATE[7]);};
if (digitalRead(enter)==LOW){VoiseAndPrint(GetBrailFromPixels(BUTTON_STATE));delay(1000); ResetAll();};
      }

 
     
     
    }


    
  

