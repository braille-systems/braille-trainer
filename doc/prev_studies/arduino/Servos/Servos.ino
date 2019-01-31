/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
bool ab[6] = {true, false, false, false, false, false};
bool bb[] = {true, true, false, false, false, false};
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


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  300 // this is the 'maximum' pulse length count (out of 4096)



 
// our servo # counter
uint8_t servonum = 0;



// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}
void parce(int number)
{
for (int servo = 0; servo < 6; servo++) {  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servo, 0, pulselen);
  }
  }
  delay (500);
  switch (number)
  {    
    case 1:
    { for (int servo = 0; servo < 6; servo++) 
        {
          if (ab[servo])
          {  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) 
            {
    pwm.setPWM(servo, 0, pulselen);
            }
           }
        }
      }
      break;

      case 2:
    { for (int servo = 0; servo < 6; servo++) 
        {
          if (bb[servo])
          {  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) 
            {
    pwm.setPWM(servo, 0, pulselen);
            }
           }
        }
      }
      break;
      
  }
}  

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
  parce(2);
}

void loop() {
  int number=2;
  
  delay(500);
/*  // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
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
}
