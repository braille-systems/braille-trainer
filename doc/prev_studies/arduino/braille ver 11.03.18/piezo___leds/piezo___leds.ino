#define clock 6
#define dat 8
#define latch 7
#define dir 9
#include <DFPlayer_Mini_Mp3.h>
#include <LedControl.h>
boolean states[8];
LedControl lc=LedControl(12,11,10,1);
char incomingByte;

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
byte numb;
void ClearBrailPanel() {
  for (byte k = 0 ; k < 8; k++)
    BUTTON_SWICH[k] = false;
}
void setMatrix(const byte c[8]) {
  for (byte i = 0; i < 8; i++) {
    lc.setRow(0, i, c[i]);
  }
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
      //mp3_play (1);
      break;
    case 2:
      setMatrix(B);
      //mp3_play (2);
      break;
    case 3:
      setMatrix(V);
      //mp3_play (3);
      break;
    case 4:
      setMatrix(G);
      //mp3_play (4);
      break;
    case 5:
      setMatrix(D);
      //mp3_play (5);
      break;
    case 6:
      setMatrix(E);
      //mp3_play (6);
      break;
    case 7:
      setMatrix(YO);
      //mp3_play (7);
      break;
    case 8:
      setMatrix(J);
      //mp3_play (8);
      break;
    case 9:
      setMatrix(Z);
      //mp3_play (9);
      break;
    case 10:
      setMatrix(I);
      //mp3_play (10);
      break;
    case 11:
      setMatrix(IY);
      //mp3_play (11);
      break;
    case 12:
      setMatrix(K);
      //mp3_play (12);
      break;
    case 13:
      setMatrix(L);
      //mp3_play (13);
      break;
    case 14:
      setMatrix(M);
      //mp3_play (14);
      break;
    case 15:
      setMatrix(N);
      //mp3_play (15);
      break;
    case 16:
      setMatrix(O);
      //mp3_play (16);
      break;
    case 17:
      setMatrix(P);
      //mp3_play (17);
      break;
    case 18:
      setMatrix(R);
      //mp3_play (18);
      break;
    case 19:
      setMatrix(S);
      //mp3_play (19);
      break;
    case 20:
      setMatrix(T);
      //mp3_play (20);
      break;
    case 21:
      setMatrix(U);
      //mp3_play (21);
      break;
    case 22:
      setMatrix(F);
      //mp3_play (22);
      break;
    case 23:
      setMatrix(X);
      //mp3_play (23);
      break;
    case 24:
      setMatrix(CE);
      //mp3_play (24);
      break;
    case 25:
      setMatrix(C);
      //mp3_play (25);
      break;
    case 26:
      setMatrix(SH);
      //mp3_play (26);
      break;
    case 27:
      setMatrix(SHA);
      //mp3_play (27);
      break;
    case 28:
      setMatrix(HARD);
      //mp3_play (28);
      break;
    case 29:
      setMatrix(YI);
      //mp3_play (30);
      break;
    case 30:
      setMatrix(SOFT);
      //mp3_play (29);
      break;
    case 31:
      setMatrix(EE);
      //mp3_play (31);
      break;
    case 32:
      setMatrix(YOU);
      //mp3_play (32);
      break;
    case 33:
      setMatrix(YA);
      //mp3_play (33);
      break;
    case 34:
      setMatrix(WAR);
      //mp3_play (44);
      break;
    case 35:
      setMatrix(QU);
      //mp3_play (45);
      break;
    case 36:
      setMatrix(DOT);
      //mp3_play (46);
      break;
    case 37:
      setMatrix(SPACE);
      //mp3_play (47);
      break;
    case 38:
      setMatrix(MINUS);
      //mp3_play (48);
      break;
    case 39:
      setMatrix(PLUS);
      //mp3_play (49);
      break;
    case 40:
      setMatrix(ZAP);
      //mp3_play (50);
      break;
    case 41:
      setMatrix(TWODOTS);
      //mp3_play (51);
      break;
    case 42:
      setMatrix(DOTZAP);
      //mp3_play (52);
      break;
    case 51:
      setMatrix(NUM_ZERO);
      //mp3_play (61);
      break;
    case 52:
      setMatrix(NUM_ONE);
      //mp3_play (62);
      break;
    case 53:
      setMatrix(NUM_TWO);
      //mp3_play (63);
      break;
    case 54:
      setMatrix(NUM_THI);
      //mp3_play (64);
      break;
    case 55:
      setMatrix(NUM_FO);
      //mp3_play (65);
      break;
    case 56:
      setMatrix(NUM_FIVE);
      //mp3_play (66);
      break;
    case 57:
      setMatrix(NUM_SIX);
      //mp3_play (67);
      break;
    case 58:
      setMatrix(NUM_SEVEN);
      //mp3_play (68);
      break;
    case 59:
      setMatrix(NUM_AIT);
      //mp3_play (69);
      break;
    case 60:
      setMatrix(NUM_NINE);
      //mp3_play (70);
      break;
    default:
      ClearBrailPanel();
      //mp3_play (98);
      break;
  }
}
int flg;
byte love[] =
{
B00001100, 
B00011110,
B00111110,
B01111100,
B01111100,
B00111110,
B00011110,
B00001100,
};

void OutGlazaLove()
{
for (int i = 0; i < 8; i++)
{
lc.setRow(0, i, love[i]);
}
}

void sendbyte(byte value){
  digitalWrite(latch, LOW);
  shiftOut(dat, clock, LSBFIRST, value);
  digitalWrite(latch, HIGH);
}

void sendpin(int pin, boolean state){
  pin--;
  states[pin]=state;
  
  byte value = 0;
  byte add = 1;
  for(int i=0; i<8; i++){
    if(states[i]==HIGH) value+=add;
    add*=2;
  }
  digitalWrite(latch, LOW);
  shiftOut(dat, clock, LSBFIRST, value);
  digitalWrite(latch, HIGH);
}

void setPiezo(){
  for (byte i=1; i<4; i++){
    sendpin(i,DatasBuffer[i+2]);
    };
  for (byte i=5; i<8; i++){
    sendpin(i,DatasBuffer[i-5]);
    };
  
  }

void cleanreg(){
  for(int i=0; i<8; i++) states[i]=LOW;
  digitalWrite(latch, LOW);
  shiftOut(dat, clock, LSBFIRST, 0);
  digitalWrite(latch, HIGH);
}

void setup() {
  pinMode(clock, OUTPUT);
  pinMode(dat, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(dir, OUTPUT);
  //digitalWrite(latch, HIGH);
  digitalWrite(dir, HIGH);
  cleanreg();
  lc.shutdown(0, false); // Включаем дисплеи
  lc.setIntensity(0, 5); // Установка яркости
  lc.clearDisplay(0); // Очищаем дисплей
  int flg=0;
  numb = 1;
  //OutGlazaLove();

}

void loop() {
/*  for (int i=1; i<9; i++)
  {sendpin(i, HIGH);
  OutGlazaLove();
  delay(200);
  lc.clearDisplay(0);
  delay(200);
  };
  for (int i=1; i<9; i++)
  {sendpin(i, LOW);
  OutGlazaLove();
  delay(200);
  lc.clearDisplay(0);
  delay(200);
  }
  */
  //sendpin(5, HIGH);
/*for (int i=1;i>33;i++){
  
 AlphavitToServo(i);
 setPiezo();
 VoiseAndPrint(i);
 delay(1000);
}*/
 AlphavitToServo(numb);
 setPiezo();
 VoiseAndPrint(numb);
  delay(1500);
  numb++;
  if (numb>60){numb=1;};
  
}
