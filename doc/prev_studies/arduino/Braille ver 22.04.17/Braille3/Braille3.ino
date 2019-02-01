//We always have to include the library
#include "LedControlMS.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

LiquidCrystal_I2C lcd(0x27, 16, 2);
/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
LedControl lc = LedControl(12, 10, 11, 1);

#define SERVOMIN  400 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // this is the 'maximum' pulse length count (out of 4096)
#define rightb 15
#define leftb 16
#define btn1 8
#define btn2 2
#define btn3 3
#define btn4 4
#define btn5 5
#define btn6 6
#define enter 7
uint8_t servonum = 0;
/* here is the data for the characters */
byte nl[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
byte a[8] = {B00011000, B00100100, B01000010, B01000010, B01111110, B01000010, B01000010, B01000010};
byte b[8] = {B01111110, B01000000, B01000000, B01111100, B01000010, B01000010, B01000010, B01111100};
byte v[8] = {B01111100, B01000010, B01000010, B01111100, B01000010, B01000010, B01000010, B01111100};
byte g[8] = {B01111110, B01000000, B01000000, B01000000, B01000000, B01000000, B01000000, B01000000};
byte d[8] = {B00011000, B00100100, B00100100, B00100100, B00100100, B00111100, B01000010, B01000010};
byte e[8] = {B01111110, B01000000, B01000000, B01111100, B01000000, B01000000, B01000000, B01111110};
byte yo[8] = {B00100100, B00000000, B01111110, B01000000, B01111000, B01000000, B01000000, B01111110};
byte zhe[8] = {B11011011, B01011010, B01111110, B00011000, B00011000, B01111110, B01011010, B11011011};
byte z[8] = {B00011100, B00100010, B00000010, B00001100, B00000010, B00000010, B00100010, B00011100};
byte i[8] = {B01000110, B01000110, B01001010, B01011010, B01011010, B01110010, B01100010, B01000010};
byte j[8] = {B00100100, B00011000, B01000010, B01000110, B01001010, B01010010, B01100010, B01000010};
byte k[8] = {B01000110, B01001000, B01010000, B01100000, B01110000, B01001000, B01000100, B01000010};
byte l[8] = {B00011000, B00100100, B00100100, B01000010, B01000010, B01000010, B10000001, B10000001};
byte m[8] = {B01000010, B01000010, B01100110, B01011010, B01011010, B01000010, B01000010, B01000010};
byte n[8] = {B01000010, B01000010, B01000010, B01111110, B01111110, B01000010, B01000010, B01000010};
byte o[8] = {B00111100, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B00111100};
byte p[8] = {B01111110, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010};
byte r[8] = {B00111000, B00100100, B00100100, B00111000, B00100000, B00100000, B00100000, B00100000};
byte s[8] = {B00011100, B00100010, B00100010, B00100000, B00100000, B00100010, B00100010, B00011100};
byte t[8] = {B11111111, B01111110, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
byte y[8] = {B01000010, B01000010, B01000010, B00111110, B00001100, B00011000, B00110000, B01100000};
byte f[8] = {B01111110, B10011001, B10011001, B10011001, B01111110, B00011000, B00011000, B00011000};
byte x[8] = {B11000011, B01100110, B00111100, B00011000, B00011000, B00111100, B01100110, B11000011};
byte tse[8] = {B01000100, B01000100, B01000100, B01000100, B01000100, B01111100, B00000010, B00000011};
byte ch[8] = {B00100100, B00100100, B00100100, B00111100, B00000100, B00000100, B00000100, B00000100};
byte sh[8] = {B10010010, B10010010, B10010010, B10010010, B10010010, B10010010, B11111110, B00000000};
byte sch[8] = {B10010010, B10010010, B10010010, B10010010, B10010010, B10010010, B11111111, B00000001};
byte tvz[8] = {B01110000, B10010000, B00010000, B00011110, B00010001, B00010001, B00010001, B00011110};
byte ii[8] = {B10000001, B10000001, B10000001, B11110001, B10001001, B10001001, B10001001, B11110001};
byte mz[8] = {B01110000, B00010000, B00010000, B00011110, B00010001, B00010001, B00010001, B00011110};
byte ee[8] = {B01111100, B00000010, B00000010, B01111110, B00000010, B00000010, B00000010, B01111100};
byte u[8] = {B01000110, B01001001, B01001001, B01111001, B01111001, B01001001, B01001001, B01000110};
byte ya[8] = {B00011110, B00100010, B00100010, B00100010, B00011110, B00010010, B00100010, B00100010};
byte smile[8] = {B00000000, B01000010, B10100101, B00000000, B00000000, B10000001, B01000010, B00111100};
byte frown[8] = {B00000000, B00000000, B11100111, B00000000, B00000000, B00000000, B01111110, B10000001};
byte dntlook[8] = {B00011000, B00100100, B00111100, B00100100, B00100100, B01100110, B11100111, B01100110};

bool ab[6] = {true, false, false, false, false, false};
bool bb[6] = {true, true, false, false, false, false};
bool vb[6] = {false, true, false, true, true, true};
bool gb[6] = {true, true, false, true, true, false};
bool db[6] = {true, false, false, true, true, false};
bool eb[6] = {true, false, false, false, true, false};
bool yob[6] = {true, false, false, false, false, true};
bool zheb[6] = {false, true, false, true, true, false};
bool zb[6] = {true, false, true, false, true, true};
bool ib[6] = {false, true, false, true, false, false};
bool jb[6] = {true, true, true, true, false, true};
bool kb[6] = {true, false, true, false, false, false};
bool lb[6] = {true, true, true, false, false, false};
bool mb[6] = {true, false, true, true, false, false};
bool nb[6] = {true, false, true, true, true, false};
bool ob[6] = {true, false, true, false, true, false};
bool pb[6] = {true, true, true, true, false, false};
bool rb[6] = {true, true, true, false, true, false};
bool sb[6] = {false, true, true, true, false, false};
bool tb[6] = {false, true, true, true, true, false};
bool yb[6] = {true, false, true, false, false, true};
bool fb[6] = {true, true, false, true, false, false};
bool xb[6] = {true, true, false, false, true, false};
bool tseb[6] = {true, false, false, true, false, false};
bool chb[6] = {true, true, true, true, true, false};
bool shb[6] = {true, false, false, false, true, true};
bool schb[6] = {true, false, true, true, false, true};
bool tvzb[6] = {true, true, true, false, true, true};
bool iib[6] = {false, true, true, true, false, true};
bool mzb[6] = {false, true, true, true, true, true};
bool eeb[6] = {false, true, false, true, false, true};
bool ub[6] = {true, true, false, false, true, true};
bool yab[6] = {true, true, false, true, false, true};
bool button [6] = {false, false, false, false, false, false};
int number;
int mode = 3;



/* we always wait a bit between updates of the display */
unsigned long delaytime = 300;



/*
  This method will display the characters for the
  word "Arduino" one after the other on the matrix.
  (you need at least 5x7 leds to see the whole chars)
*/
//Function to control LED depending on number of symbol
void parce(int num)
{

  switch (num)
  {
    case 0:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, nl[row]);
        }
      }
      break;
    case 1:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, a[row]);
        }
      }

      break;
    case 2:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, b[row]);
        }

      }
      break;
    case 3:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, v[row]);
        }
      }
      break;
    case 4:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, g[row]);
        }
      }
      break;
    case 5:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, d[row]);
        }
      }
      break;
    case 6:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, e[row]);
        }
      }
      break;
    case 7:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, yo[row]);
        }
      }
      break;
    case 8:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, zhe[row]);
        }
      }
      break;
    case 9:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, z[row]);
        }
      }
      break;
    case 10:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, i[row]);
        }
      }
      break;
    case 11:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, j[row]);
        }
      }
    case 12:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, k[row]);
        }
      }
      break;
    case 13:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, l[row]);
        }
      }
      break;
    case 14:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, m[row]);
        }
      }
      break;
    case 15:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, n[row]);
        }
      }
      break;
    case 16:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, o[row]);
        }
      }
      break;
    case 17:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, p[row]);
        }
      }
      break;
    case 18:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, r[row]);
        }
      }
      break;
    case 19:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, s[row]);
        }
      }
    case 20:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, t[row]);
        }
      }
      break;
    case 21:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, y[row]);
        }
      }
      break;
    case 22:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, f[row]);
        }
      }
      break;
    case 23:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, x[row]);
        }
      }
      break;
    case 24:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, tse[row]);
        }
      }
      break;
    case 25:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, ch[row]);
        }
      }
    case 26:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, sh[row]);
        }
      }
      break;
    case 27:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, sch[row]);
        }
      }
      break;
    case 28:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, tvz[row]);
        }
      }
      break;
    case 29:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, ii[row]);
        }
      }
      break;
    case 30:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, mz[row]);
        }
      }
      break;
    case 31:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, ee[row]);
        }
      }
      break;
    case 32:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, u[row]);
        }
      }
      break;
    case 33:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, ya[row]);
        }
      }
      break;
    case 34:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, smile[row]);
        }
      }
      break;
    case 35:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, frown[row]);
        }
      }
      break;
    case 36:
    { for (int row = 0; row < 8; row++) {
          lc.setRow(0, row, dntlook[row]);
        }
      }
      break;
    case 37:
      {
      }
      break;
    case 38:
      {
      }
      break;
    case 39:
      {
      }
      break;
    case 40:
      {
      }
      break;
  }

}
//Function to control motors depending on nubmer of symbol
void parce2(int num)
{
  for (int servo = 0; servo < 6; servo++)
  { Serial.println(servonum);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--)
    {
      pwm.setPWM(servo, 0, pulselen);
    }
  }
  delay(300);
  switch (num)
  {
    case 0:
      {
      }
      break;
    case 1:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (ab[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }

      break;
    case 2:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (bb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 3:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (vb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 4:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (gb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 5:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (db[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 6:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (eb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 7:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (yob[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 8:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (zheb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 9:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (zb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 10:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (ib[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 11:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (jb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
    case 12:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (kb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 13:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (lb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 14: {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (mb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 15:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (nb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 16:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (ob[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 17:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (pb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 18:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (rb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 19:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (sb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
    case 20:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (tb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 21:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (yb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 22:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (fb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 23:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (xb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 24:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (tseb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
      break;
    case 25:
      {
        { for (int servo = 0; servo < 6; servo++)
          {
            if (chb[servo])
            { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
              {
                pwm.setPWM(servo, 0, pulselen);
              }
            }
          }
        }
      }
    case 26:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (shb[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 27:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (schb[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 28:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (tvzb[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 29:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (iib[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 30:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (mzb[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 31:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (eeb[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 32:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (ub[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;
    case 33:
      { for (int servo = 0; servo < 6; servo++)
        {
          if (yab[servo])
          { for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
            {
              pwm.setPWM(servo, 0, pulselen);
            }
          }
        }
      }
      break;

  }

}
//Function which compares array from "lib" with array from byttons
bool check(bool b1, bool b2, bool b3, bool b4, bool b5, bool b6)
{
  if (button[0] == b1 && button[1] == b2 && button[2] == b3 && button[3] == b4 && button[4] == b5 && button[5] == b6) {
    return true;
  } else {
    return false;
  };
}

//Function which checks each symbol in array from "lib"
int deparce()
{
  if (check(ab[0],ab[1],ab[2],ab[3],ab[4],ab[5])) {
    return 1;
  };
  if (check(bb[0],bb[1],bb[2],bb[3],bb[4],bb[5])) {
    return 2;
  };
  if (check(vb[0],vb[1],vb[2],vb[3],vb[4],vb[5])) {
    return 3;
  };
  if (check(gb[0],gb[1],gb[2],gb[3],gb[4],gb[5])) {
    return 4;
  };
  if (check(db[0],db[1],db[2],db[3],db[4],db[5])) {
    return 5;
  };
  if (check(eb[0],eb[1],eb[2],eb[3],eb[4],eb[5])) {
    return 6;
  };
  if (check(yob[0],yob[1],yob[2],yob[3],yob[4],yob[5])) {
    return 7;
  };
  if (check(zheb[0],zheb[1],zheb[2],zheb[3],zheb[4],zheb[5])) {
    return 8;
  };
  if (check(zb[0],zb[1],zb[2],zb[3],zb[4],zb[5])) {
    return 9;
  };
  if (check(ib[0],ib[1],ib[2],ib[3],ib[4],ib[5])) {
    return 10;
  };
  if (check(jb[0],jb[1],jb[2],jb[3],jb[4],jb[5])) {
    return 11;
  };
  if (check(kb[0],kb[1],kb[2],kb[3],kb[4],kb[5])) {
    return 12;
  };
  if (check(lb[0],lb[1],lb[2],lb[3],lb[4],lb[5])) {
    return 13;
  };
  if (check(mb[0],mb[1],mb[2],mb[3],mb[4],mb[5])) {
    return 14;
  };
  if (check(nb[0],nb[1],nb[2],nb[3],nb[4],nb[5])) {
    return 15;
  };
  if (check(ob[0],ob[1],ob[2],ob[3],ob[4],ob[5])) {
    return 16;
  };
  if (check(pb[0],pb[1],pb[2],pb[3],pb[4],pb[5])) {
    return 17;
  };
  if (check(rb[0],rb[1],rb[2],rb[3],rb[4],rb[5])) {
    return 18;
  };
  if (check(sb[0],sb[1],sb[2],sb[3],sb[4],sb[5])) {
    return 19;
  };
  if (check(tb[0],tb[1],tb[2],tb[3],tb[4],tb[5])) {
    return 20;
  };
  if (check(yb[0],yb[1],yb[2],yb[3],yb[4],yb[5])) {
    return 21;
  };
  if (check(fb[0],fb[1],fb[2],fb[3],fb[4],fb[5])) {
    return 22;
  };
  if (check(xb[0],xb[1],xb[2],xb[3],xb[4],xb[5])) {
    return 23;
  };
  if (check(tseb[0],tseb[1],tseb[2],tseb[3],tseb[4],tseb[5])) {
    return 24;
  };
  if (check(chb[0],chb[1],chb[2],chb[3],chb[4],chb[5])) {
    return 25;
  };
  if (check(shb[0],shb[1],shb[2],shb[3],shb[4],shb[5])) {
    return 26;
  };
  if (check(schb[0],schb[1],schb[2],schb[3],schb[4],schb[5])) {
    return 27;
  };
  if (check(tvzb[0],tvzb[1],tvzb[2],tvzb[3],tvzb[4],tvzb[5])) {
    return 28;
  };
  if (check(iib[0],iib[1],iib[2],iib[3],iib[4],iib[5])) {
    return 29;
  };
  if (check(mzb[0],mzb[1],mzb[2],mzb[3],mzb[4],mzb[5])) {
    return 30;
  };
  if (check(eeb[0],eeb[1],eeb[2],eeb[3],eeb[4],eeb[5])) {
    return 31;
  };
  if (check(ub[0],ub[1],ub[2],ub[3],ub[4],ub[5])) {
    return 32;
  };
  if (check(yab[0],yab[1],yab[2],yab[3],yab[4],yab[5])) {
    return 33;
  }
  else return (35);
  //return(35);
}

void setup() {
  Serial.begin(9600);
  //mp3 setup code
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (30);
  // lcd setup code
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Hello, Braille!");
  lcd.setCursor(2, 1);
  lcd.print("Viva Fab Lab!");
  parce(34);
  delay (1000);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
/*  lcd.setCursor(5, 0);
  lcd.print("Alphabet");
  lcd.setCursor(0, 1);
  lcd.print("Choose letter");
  number = 1;*/
  //pinMode(okb, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);
  pinMode(btn6, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);

  //parce(1);


  // led setup code
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 1);
  /* and clear the display */
  lc.clearDisplay(0);
  // servo setup code

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();

  parce(34);
  parce2(1);
  mp3_play(0);
  mp3_play(34);
}

void mode3 ()
{
  parce(34);
  //parce2(34);
  //mp3_play(34);
  lcd.setCursor(0, 0);
  lcd.print("Write in Braille");
  lcd.setCursor(0, 1);
  lcd.print("and press Enter");
  do {
    if (digitalRead(btn1) == LOW) {
      button[0] = true;
      Serial.println("b1");
      delay(200);
    };
    if (digitalRead(btn2) == LOW) {
      button[1] = true;
      Serial.println("b2");
      delay(200);
    };
    if (digitalRead(btn3) == LOW) {
      button[2] = true;
      Serial.println("b3");
      delay(200);
    };
    if (digitalRead(btn4) == LOW) {
      button[3] = true;
      Serial.println("b4");
      delay(200);
    };
    if (digitalRead(btn5) == LOW) {
      button[4] = true;
      Serial.println("b5");
      delay(200);
    };
    if (digitalRead(btn6) == LOW) {
      button[5] = true;
      Serial.println("b6");
      delay(200);
    };
  /*  if (digitalRead(mode1b)==LOW)
    {
      mode=1;
      break;
    }*/
 /*   if (digitalRead(mode2b)==LOW)
    {
      mode=2;
      break;
    }*/
  }
  while (digitalRead(enter) == HIGH);
  if (deparce()==35){lcd.setCursor(0, 0);
  lcd.print("Invalid symbol  ");
  lcd.setCursor(0, 1);
  lcd.print("    Try again   ");
  mp3_play(35);}
  
  else
  {
  lcd.setCursor(0, 0);
  lcd.print("Your symbol is: ");
  lcd.setCursor(0, 1);
  lcd.print("                ");}
  parce(deparce());
  parce2(deparce());
  mp3_play(deparce());
  //Serial.println(analogRead(A0));
  for (int defcounter=0;defcounter<6;defcounter++){ Serial.print(button[defcounter]);};Serial.println(" ");
  for (int defcounter=0;defcounter<6;defcounter++){ Serial.print(ab[defcounter]);};Serial.println(" ");
  delay (1000);
  for (int fu = 0; fu < 6; fu++)
  {
    button[fu] = {false};
  };
 for (int defcounter=0;defcounter<6;defcounter++){ Serial.print(button[defcounter]);};Serial.println(" ");
}

//This function I wrote to test LED matrix & parce function
void glebkryt()
{
  parce(4);
  delay(delaytime);
  parce(13);
  delay(delaytime);
  parce(6);
  delay(delaytime);
  parce(2);
  delay(delaytime);
  parce(0);
  delay(delaytime * 2);
  parce(12);
  delay(delaytime);
  parce(18);
  delay(delaytime);
  parce(21);
  delay(delaytime);
  parce(20);
  delay(delaytime);

}

//default LED matrix function
void writeArduinoOnMatrix() {


  /* now display them one by one with a small delay */


  lc.setRow(0, 0, a[0]);
  lc.setRow(0, 1, a[1]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[3]);
  lc.setRow(0, 4, a[4]);
  lc.setRow(0, 5, a[5]);
  lc.setRow(0, 6, a[6]);
  lc.setRow(0, 7, a[7]);
  lc.setRow(0, 8, a[8]);
  delay(delaytime);
  lc.setRow(0, 0, r[0]);
  lc.setRow(0, 1, r[1]);
  lc.setRow(0, 2, r[2]);
  lc.setRow(0, 3, r[3]);
  lc.setRow(0, 4, r[4]);
  lc.setRow(0, 5, r[5]);
  lc.setRow(0, 6, r[6]);
  lc.setRow(0, 7, r[7]);
  lc.setRow(0, 8, r[8]);
  delay(delaytime);
  lc.setRow(0, 0, d[0]);
  lc.setRow(0, 1, d[1]);
  lc.setRow(0, 2, d[2]);
  lc.setRow(0, 3, d[3]);
  lc.setRow(0, 4, d[4]);
  lc.setRow(0, 5, d[5]);
  lc.setRow(0, 6, d[6]);
  lc.setRow(0, 7, d[7]);
  lc.setRow(0, 8, d[8]);
  delay(delaytime);
  lc.setRow(0, 0, u[0]);
  lc.setRow(0, 1, u[1]);
  lc.setRow(0, 2, u[2]);
  lc.setRow(0, 3, u[3]);
  lc.setRow(0, 4, u[4]);
  lc.setRow(0, 5, u[5]);
  lc.setRow(0, 6, u[6]);
  lc.setRow(0, 7, u[7]);
  lc.setRow(0, 8, u[8]);
  delay(delaytime);
  lc.setRow(0, 0, i[0]);
  lc.setRow(0, 1, i[1]);
  lc.setRow(0, 2, i[2]);
  lc.setRow(0, 3, i[3]);
  lc.setRow(0, 4, i[4]);
  lc.setRow(0, 5, i[5]);
  lc.setRow(0, 6, i[6]);
  lc.setRow(0, 7, i[7]);
  lc.setRow(0, 8, i[8]);
  delay(delaytime);
  lc.setRow(0, 0, n[0]);
  lc.setRow(0, 1, n[1]);
  lc.setRow(0, 2, n[2]);
  lc.setRow(0, 3, n[3]);
  lc.setRow(0, 4, n[4]);
  lc.setRow(0, 5, n[5]);
  lc.setRow(0, 6, n[6]);
  lc.setRow(0, 7, n[7]);
  lc.setRow(0, 8, n[8]);
  delay(delaytime);
  lc.setRow(0, 0, o[0]);
  lc.setRow(0, 1, o[1]);
  lc.setRow(0, 2, o[2]);
  lc.setRow(0, 3, o[3]);
  lc.setRow(0, 4, o[4]);
  lc.setRow(0, 5, o[5]);
  lc.setRow(0, 6, o[6]);
  lc.setRow(0, 7, o[7]);
  lc.setRow(0, 8, o[8]);
  delay(delaytime);
  /*lc.setRow(0,0,dntlook[0]);
    lc.setRow(0,1,dntlook[1]);
    lc.setRow(0,2,dntlook[2]);
    lc.setRow(0,3,dntlook[3]);
    lc.setRow(0,4,dntlook[4]);
    lc.setRow(0,5,dntlook[5]);
    lc.setRow(0,6,dntlook[6]);
    lc.setRow(0,7,dntlook[7]);
    lc.setRow(0,8,dntlook[8]);
    delay(delaytime);
    delay(delaytime);
  */
  lc.setRow(0, 0, 0);
  lc.setRow(0, 1, 0);
  lc.setRow(0, 2, 0);
  lc.setRow(0, 3, 0);
  lc.setRow(0, 4, 0);
  lc.setRow(0, 5, 0);
  lc.setRow(0, 6, 0);
  lc.setRow(0, 7, 0);
  lc.setRow(0, 8, 0);
  delay(delaytime);
}

void mode1()
{
  if (digitalRead (rightb) == HIGH)
  { number++;
    if (number == 34) {
      number = 1;
    };
    parce(number);
    parce2(number);
    delay(300);
    Serial.println(number);
  };
  if (digitalRead (leftb) == HIGH)
  { number--;
    if (number == 0) {
      number = 33;
    };
    parce(number);
    parce2(number);
    delay(300);
    Serial.println(number);
  };
}
 
void mode2()
{
  if (digitalRead (rightb) == HIGH)
  { number++;
    if (number == 34) {
      number = 1;
    };
    parce(number);
    delay(300);
    Serial.println(number);
  };
  if (digitalRead (leftb) == HIGH)
  { number--;
    if (number == 0) {
      number = 33;
    };
    parce(number);
    delay(300);
    Serial.println(number);
  };
//  if (digiralRead (enterb)== HIGH){parce2(number); delay (1000); parce2(0);};
}



void loop() {
  /*
    lc.setRow(0, 0, 0);
    lc.setRow(0, 1, 0);
    lc.setRow(0, 2, 0);
    lc.setRow(0, 3, 0);
    lc.setRow(0, 4, 0);
    lc.setRow(0, 5, 0);
    lc.setRow(0, 6, 0);
    lc.setRow(0, 7, 0);
    lc.setRow(0, 8, 0);

    delay(delaytime);
    parce(16);
     delay(delaytime*4);
  */
  /*  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
    }

    delay(500);

    servonum ++;

    if (servonum > 5) servonum = 0;

  */

  // glebkryt();
/*  if (mode == 1) {
    mode1();
  };
  if (mode == 3) {
    mode3();
  };
  */
/*
  if (digitalRead (rightb) == HIGH)
  { number++;
    if (number == 34) {
      number = 1;
    };
    parce(number);
    parce2(number);
    delay(300);
    Serial.println(number);
  };
  if (digitalRead (leftb) == HIGH)
  { number--;
    if (number == 0) {
      number = 33;
    };
    parce(number);
    parce2(number);
    delay(300);
    Serial.println(number);
  };
*/
mode3();
}
