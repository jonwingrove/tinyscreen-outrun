#include <TinyScreen.h>
#include <SPI.h>
#include <Wire.h>
#include "Sprite.h"
#include "Joystick.h"
#include "Car.h"
#include <SD.h>
#include <avr/pgmspace.h>

#include "Hills.h"

const uint8_t PROGMEM s_CarBackData[] {0xba,0xba,0xba,0xba,0xba,0xba,0x02,0x03,0x03,0x4b,0x4b,0x03,0x03,0x02,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0x03,0xf2,0xf2,0xf2,0xff,0xf2,0xf2,0xf2,0xf2,0x03,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0x02,0xf2,0xf2,0xff,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0x02,0xba,0xba,0xba,0xba
,0xba,0x03,0xba,0x02,0x03,0xf2,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x02,0xba,0x03,0xba
,0xba,0x02,0xba,0x02,0x03,0xf2,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x02,0xba,0x02,0xba
,0x02,0x03,0x4b,0x4b,0x4b,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02
,0x03,0x03,0x03,0x4b,0x93,0x93,0x4b,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
,0x03,0x13,0x13,0x00,0x03,0x03,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x03,0x03,0x00,0x13,0x13,0x03
,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
,0x02,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x02
,0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02
,0x02,0x4b,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x03,0x4b,0x02
,0xba,0x00,0x00,0x00,0x00,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0xba
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba
};
static Sprite s_CarBack = {20,15, s_CarBackData };

const uint8_t PROGMEM s_CarLeftData[] {0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x03,0x4b,0x93,0x4b,0x4b,0x02,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0x03,0x02,0xf2,0xff,0xf2,0xf2,0xf2,0xf2,0x03,0x03,0x02,0xba,0xba,0xba,0xba,0xba
,0xba,0x02,0x02,0xf2,0xf2,0x02,0x03,0xf2,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0xba,0xba,0xba,0xba,0xba
,0x02,0x02,0xf2,0x02,0xf2,0x03,0x03,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x02,0xba,0x03,0xba
,0x02,0x03,0x02,0xf2,0x02,0x03,0x03,0xf2,0xf2,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x02,0xba,0x02,0xba
,0x00,0x00,0x4b,0x03,0x4b,0x4b,0x4b,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02
,0x00,0x00,0x03,0x03,0x03,0x4b,0x93,0x93,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x4b,0x4b,0x03
,0x00,0x02,0x03,0x13,0x13,0x00,0x03,0x03,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x03,0x03,0x00,0x13,0x13,0x03
,0x00,0x02,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
,0x00,0x02,0x02,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x02
,0x00,0xff,0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02
,0x00,0xff,0x02,0x03,0x03,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x03,0x4b,0x02
,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0xba
,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba
,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba
};
const static Sprite s_CarLeft = {21,15,s_CarLeftData };

const uint8_t PROGMEM s_CarRightData[] {0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x02,0x4b,0x93,0x4b,0x4b,0x03,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0x02,0x03,0x03,0xf2,0xff,0xf2,0xf2,0xf2,0xf2,0x02,0x03,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0x03,0xf2,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0x03,0x02,0xf2,0xf2,0x02,0x02,0xba
,0xba,0x03,0xba,0x02,0x03,0xf2,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x03,0xf2,0x02,0xf2,0x02,0x02
,0xba,0x02,0xba,0x02,0x03,0xf2,0xf2,0xff,0xff,0xf2,0xf2,0xf2,0xf2,0xf2,0x03,0x03,0x02,0xf2,0x02,0x03,0x02
,0x02,0x03,0x4b,0x4b,0x4b,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x4b,0x00,0x00
,0x03,0x03,0x03,0x4b,0x93,0x93,0x4b,0x4b,0x4b,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x4b,0x4b,0x03,0x00,0x00
,0x03,0x13,0x13,0x00,0x03,0x03,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x03,0x03,0x00,0x13,0x13,0x03,0x02,0x00
,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x00
,0x02,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x02,0x02,0x00
,0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0x00
,0x02,0x4b,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0xff,0x00,0x02,0x02,0x02,0x02,0x03,0x03,0x02,0xff,0x00
,0xba,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0xba
,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba
,0xba,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0xba
};
static Sprite s_CarRight = {21,15,s_CarRightData };

const uint8_t PROGMEM s_SmokeData[] {0xba,0xba,0xba,0xba,0xb6,0xb6,0xff,0xff,0xb6,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0x49,0x91,0xb6,0xb6,0xb6,0xb6,0xb6,0xba,0xba,0xba
,0xba,0xba,0x91,0x91,0xb6,0xb6,0xb6,0xb6,0xff,0xff,0xba,0xba,0xba
,0xba,0xba,0x91,0x49,0xb6,0x91,0xff,0xff,0xff,0xff,0xff,0xba,0xba
,0xba,0x24,0x91,0xb6,0xb6,0x91,0xb6,0xb6,0xff,0xff,0xff,0xba,0xba
,0xba,0x24,0x91,0x91,0x91,0xb6,0xb6,0xb6,0xb6,0xb6,0xff,0xba,0xba
,0xba,0xba,0x91,0x91,0xb6,0xb6,0xb6,0xb6,0xb6,0xff,0xba,0xba,0xba
,0xba,0xba,0x49,0x91,0x91,0x91,0xb6,0x91,0x91,0xff,0xba,0xba,0xba
,0xba,0xba,0x24,0x49,0x91,0x91,0xb6,0xff,0xff,0xff,0xba,0xba,0xba
,0xba,0xba,0xba,0x24,0x24,0x49,0x24,0xb6,0xb6,0xff,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0x24,0x91,0xb6,0xb6,0xb6,0xb6,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0x24,0x91,0x91,0x24,0xb6,0x91,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0x24,0x24,0xb6,0xb6,0x91,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0x91,0x24,0x91,0xff,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0x91,0x24,0xb6,0xb6,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0x24,0x91,0x24,0xb6,0xff,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x24,0xb6,0x24,0xb6,0xff,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x24,0x91,0x91,0xff,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x24,0xff
};
static Sprite s_Smoke = {13,19,s_SmokeData };

const uint8_t PROGMEM s_Cloud1Data[] {0xbe,0xbe,0xbe,0xbe,0xba,0xba,0xba,0xba,0xbe,0xbe,0xbe,0xbe,0xd9,0xfa,0xd9,0xd9,0xbe,0xbe,0xbe,0xbe,0xff,0xda,0xda,0xda,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xbe,0xbe,0xbe,0xbe,0xba,0xba,0xba,0xba,0xbe,0xbe,0xbe,0xda,0xda,0xda,0xda,0xfa,0xbe,0xbe,0xbe,0xda,0xda,0xda,0xff,0xff,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xbe,0xbe,0xbe,0xbe,0xfa,0xba,0xba,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xbe,0xbe,0xbe,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xfa,0xba,0xba,0xba,0xba
,0xba,0xd5,0xd5,0xd5,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xd6,0xd6,0xd6,0xd6,0xd5,0xba,0xba,0xba
,0xd1,0xd5,0xd5,0xd5,0xda,0xd5,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xd1,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xd1,0xd6,0xd6,0xd6,0xd5,0xd5,0xd5,0xba
,0xba,0xd1,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd6,0xd6,0xd1,0xd5,0xd5,0xd1,0xd1
,0xba,0xba,0xba,0xba,0xda,0xd0,0xda,0xda,0xd0,0xd0,0xd0,0xda,0xda,0xda,0xd0,0xd0,0xd0,0xd0,0xda,0xd0,0xda,0xda,0xd0,0xd0,0xd0,0xd1,0xd6,0xd0,0xba,0xba,0xba,0xba
};
static Sprite s_Cloud1 = {32,8, s_Cloud1Data };

const uint8_t PROGMEM s_AwesomeTreeData[] {0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x99,0xba,0xba,0xba,0xba,0x75,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0x75,0x75,0x51,0x0c,0x0c,0xba,0x95,0x2c,0x51,0x10,0xba,0x08,0x08,0x50,0x10,0x08,0x71,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0x51,0x0c,0x0c,0x0c,0x08,0x08,0x0c,0x08,0x51,0x08,0x04,0x04,0x04,0x04,0x2c,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0x75,0x2c,0x30,0x0c,0x08,0x08,0x08,0x0c,0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x0c,0x75,0x75,0x30,0xba,0xba,0xba
,0xba,0xba,0x2c,0x0c,0x08,0x04,0x00,0x00,0x04,0x00,0x04,0x0c,0x08,0x08,0x08,0x08,0x0c,0x08,0x04,0x4c,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0x95,0x08,0x00,0x00,0x04,0x08,0x0c,0x0c,0x10,0x08,0x28,0x2c,0x0c,0x0c,0x08,0x08,0x08,0x04,0x2c,0xba,0xba,0xba,0xba
,0xba,0xba,0x71,0x04,0x08,0x2c,0x08,0x0c,0x08,0x10,0x0c,0x00,0x08,0x08,0x04,0x08,0x08,0x08,0x0c,0x0c,0x00,0x0c,0xba,0xba,0xba
,0xba,0xba,0x4d,0x08,0x2c,0x08,0x04,0x04,0x04,0x0c,0x00,0x04,0x0c,0x08,0x08,0x04,0x04,0x04,0x08,0x0c,0x04,0x04,0x79,0xba,0xba
,0xba,0xba,0x0c,0x08,0x04,0x04,0x00,0x00,0x08,0x08,0x00,0x08,0x08,0x00,0x0c,0x08,0x04,0x04,0x04,0x08,0x08,0x96,0x50,0xba,0xba
,0xba,0x51,0x08,0x28,0xba,0xba,0x4d,0x04,0x0c,0x04,0x08,0x08,0x04,0x00,0x28,0x99,0x28,0x04,0x04,0x00,0x04,0xba,0xba,0xba,0xba
,0xba,0xba,0x75,0x95,0xba,0xba,0x51,0x55,0xba,0x51,0x08,0x04,0x04,0x04,0x04,0xba,0xba,0x28,0x04,0x04,0x08,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0x51,0xba,0xba,0x28,0x08,0x04,0x08,0x08,0x0c,0x51,0xba,0xba,0x08,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x04,0x04,0x08,0x09,0x08,0xb9,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x00,0x09,0x09,0x2d,0x09,0x4d,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x29,0x09,0x29,0x29,0x2d,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
};
static Sprite s_AwesomeTree = {25,16, s_AwesomeTreeData };

uint8_t ALPHA = 0xBA;

TinyScreen display = TinyScreen(0);

  int xx = 0;
  int xd = 1;
SpriteInst sprites[10];

int playerSprite = 7;
int smokeSpriteL = 8;
int smokeSpriteR = 9;
int cloudSprite1 = 2;
int cloudSprite2 = 3;

float s_camPos = 0;
Car s_car;
bool s_hasSDCard;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  display.begin();

  s_hasSDCard = SD.begin(10);
  
  s_car.xPos = 0;
  s_car.zPos = 0;
  s_car.currentSpeed = 0;
  s_car.currentAngle = 0;
//  display.setBrightness(brightness);

//memset(sprites,0,sizeof(SpriteInst)*10);

  sprites[playerSprite].enabled = true;
  sprites[playerSprite].sprite = &s_CarBack;
  
  sprites[smokeSpriteL].sprite = &s_Smoke;
  sprites[smokeSpriteR].sprite = &s_Smoke;
  sprites[smokeSpriteR].flipX = true;
  
  sprites[0].x = -2;
  sprites[0].y = 21;
  sprites[0].sprite = &s_Hills;
  sprites[0].enabled = true;
  sprites[0].scaleShift = 1;
  
  sprites[cloudSprite1].x = 48;
  sprites[cloudSprite1].y = 14;
  sprites[cloudSprite1].sprite = &s_Cloud1;
  sprites[cloudSprite1].enabled = true;
  
  sprites[cloudSprite2].x = 0;
  sprites[cloudSprite2].y = 16;
  sprites[cloudSprite2].sprite = &s_Cloud1;
  sprites[cloudSprite2].enabled = true;
}

uint8_t s_skyBlue = 0xf8;
uint8_t s_groundGreen = 0x08;
uint8_t s_darkGrey = 0x49;
uint8_t s_lightGrey = 0xb6;
float roadPos[8] = {0,1,0,-2,0,1,3,0};

float getRoadPosAt(int playerPos)
{
  float normalisedPlayerPos = playerPos / 255.0f;
  int lowerBound = floor(normalisedPlayerPos);
  int upperBound = floor(normalisedPlayerPos+1);
  float amt = normalisedPlayerPos - lowerBound;
  
  return roadPos[lowerBound%8]*(1-amt) + roadPos[upperBound%8]*amt;
}

void drawRoadSection(uint8_t* lineBuffer, int distance, int playerPos, int width, float camPos)
{
  float pos = playerPos + distance;
  memset(lineBuffer, s_groundGreen, 96);
  int pDist = (int)pos;
  uint8_t col = (pDist>>4)%2 == 0 ? s_darkGrey : s_lightGrey;
  
  int ctr = (48+(40*getRoadPosAt(pos)))-(camPos*40);
  int left = min(max(ctr-width,0),95);
  int right = max(min(ctr+width,95),0);
  
  memset(lineBuffer+left, col, right-left);
}

void doLine(uint8_t* lineBuffer, int lineIndex)
{
  if ( lineIndex < 31 )
  {
    memset(lineBuffer, s_skyBlue, 96);
  }
  else  
  {
    //float pH = 1 - ((float)(lineIndex - 31))/32.0f;
    int pH = 32 - (lineIndex - 31);
    // divide by 32... >> 5, divide by 32*32 >> 10
    int distance = (pH*pH) >> 2;
    int width = 8 + (lineIndex - 31);
    drawRoadSection(lineBuffer, distance, s_car.zPos, width, s_camPos); 
  }
}

char s_filename[32];
File s_writeFile;
void processScreen(int saveScreenshot)
{

  if (saveScreenshot != -1) 
  {
    memset(s_filename,0,32);
    sprintf(s_filename,"s%d",saveScreenshot);
    s_writeFile = SD.open(s_filename, FILE_WRITE);
    s_writeFile.seek(0);
  }
  else
  {  
    display.goTo(0,0);
    display.startData();
  }
  
  uint8_t lineBuffer[96];
  uint8_t alphaColor = ALPHA;

  for(int lines = 0; lines < 64; ++lines)
  {
    memset(lineBuffer,0,96);
    doLine(lineBuffer, lines);
    int numSprites = 10;
    for(int index = 0; index < numSprites; ++index)
    {
      if(sprites[index].enabled)
      { 
        const Sprite* spriteType = sprites[index].sprite;
        int adjustedHeight = spriteType->height << sprites[index].scaleShift;
        int adjustedWidth = spriteType->width << sprites[index].scaleShift;
        int yTop = sprites[index].y - (adjustedHeight >> 1);
        
        int curLine = lines - yTop;
        if ( curLine >= 0 && curLine < adjustedHeight )
        {
          if ( sprites[index].flipY )
          {
            curLine = (adjustedHeight-1)-curLine;
          }
          int xLeft = sprites[index].x - (adjustedWidth >> 1);
          int startX = max(-xLeft,0);
          for(int x = startX; x < adjustedWidth; ++x)
          {
            int tx = x + xLeft;
            if ( tx >= 0 && tx < 96 )
            {
//              uint8_t col = sprites[index].flip ? spriteType->data[(spriteType->width-(x+1))+(curLine*spriteType->width)] : spriteType->data[x+(curLine*spriteType->width)];
              //int offset = sprites[index].flipX ? (spriteType->width-(x+1))+(curLine*spriteType->width) : x+(curLine*spriteType->width);
              int pixX = sprites[index].flipX ? (adjustedWidth-1)-x : x;

              int remapX = min(pixX >> sprites[index].scaleShift, spriteType->width-1);
              int remapY = min(curLine >> sprites[index].scaleShift, spriteType->height-1);

              int offset = remapX+(remapY*spriteType->width);
              
              uint8_t col = pgm_read_byte_near(spriteType->data + offset);
              if ( col != alphaColor )
              {
                lineBuffer[tx] = col;
              }
            }
            else
            {
              break;
            }
          }
        }
      }    
    }

    if(saveScreenshot != -1)
    {
      s_writeFile.write(lineBuffer,96);
    }
    else
    {
      display.writeBuffer(lineBuffer,96);
    }
  }
  
  if(saveScreenshot != -1)
  {
    s_writeFile.close();
  }
  else
  {
    display.endTransfer();
  }
}

int s_screenshotIndex = 0;

void loop() {
  
  sprites[cloudSprite1].x--;
  if ( sprites[cloudSprite1].x < -20 )
  {
    sprites[cloudSprite1].x = 120;
  }
  sprites[cloudSprite2].x--;
  if ( sprites[cloudSprite2].x < -20 )
  {
    sprites[cloudSprite2].x = 120;
  }
  
  
  s_camPos = (s_car.xPos + getRoadPosAt(s_car.zPos + 6)) / 2;
  
  sprites[0].x = -s_camPos*8;
  // put your main code here, to run repeatedly:
  sprites[playerSprite].x = (48) - (s_camPos*40) + (s_car.xPos*40);
  sprites[playerSprite].y = 56;

  if ( s_joystickData.b1 )
  {
    processScreen(-1);
    processScreen(s_screenshotIndex++);
  }
  else
  {
    processScreen(-1);
  }
  getJoystick();
  filterData(150);

  
  s_car.currentSpeed += s_joystickData.b2 ? 3.2f : 0;
  s_car.currentAngle += s_joystickData.LX * 0.001f;
  
  if ( s_car.currentSpeed > 25.0f )
  {
    s_car.currentSpeed = 25.0f;
  }
  if(s_car.currentSpeed < 0 )
  {
    s_car.currentSpeed = 0;
  }
  s_car.currentSpeed *= 0.9f;
  s_car.currentAngle *= 0.6f;
  
  s_car.xPos += s_car.currentAngle * 0.02f * s_car.currentSpeed;
  
  s_car.zPos += s_car.currentSpeed;
  
  if ( s_car.currentAngle > 0.1f )
  {
    sprites[playerSprite].sprite = &s_CarRight;
  }
  else if ( s_car.currentAngle < -0.1f )
  {
    sprites[playerSprite].sprite = &s_CarLeft;
  }
  else
  {
    sprites[playerSprite].sprite = &s_CarBack;    
  }  
  
  float currentPos = getRoadPosAt(s_car.zPos);
  if (( s_car.xPos > currentPos + 1)||( s_car.xPos < currentPos - 1))
  {
    s_car.currentSpeed *= 0.5f;
    sprites[smokeSpriteL].enabled = true;
    sprites[smokeSpriteR].enabled = true;
    
    sprites[smokeSpriteL].x = 48-7 - (s_camPos*40) + (s_car.xPos*40);
    sprites[smokeSpriteL].y = 64-13;
    
    sprites[smokeSpriteR].x = 48+7 - (s_camPos*40) + (s_car.xPos*40);
    sprites[smokeSpriteR].y = 64-13;
  }
  else  
  {
    sprites[smokeSpriteL].enabled = false;
    sprites[smokeSpriteR].enabled = false;
  }
}
