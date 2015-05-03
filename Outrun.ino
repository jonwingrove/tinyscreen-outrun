#include <TinyScreen.h>
#include <SPI.h>
#include <Wire.h>
#include "Sprite.h"
#include "Joystick.h"
#include "Car.h"

const static Sprite s_CarBack = {20,15, new uint8_t[300] {0xba,0xba,0xba,0xba,0xba,0xba,0x02,0x03,0x03,0x4b,0x4b,0x03,0x03,0x02,0xba,0xba,0xba,0xba,0xba,0xba
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
}};

const static Sprite s_CarLeft = {21,15, new uint8_t[315] {0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x03,0x4b,0x93,0x4b,0x4b,0x02,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba
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
}};

const static Sprite s_CarRight = {21,15, new uint8_t[315] {0xba,0xba,0xba,0xba,0xba,0xba,0xba,0xba,0x02,0x4b,0x93,0x4b,0x4b,0x03,0xba,0xba,0xba,0xba,0xba,0xba,0xba
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
}};

static Sprite s_Smoke = {13,19, new uint8_t[247] {0xba,0xba,0xba,0xba,0xb6,0xb6,0xff,0xff,0xb6,0xba,0xba,0xba,0xba
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
}};

uint8_t ALPHA = 0xBA;

TinyScreen display = TinyScreen(0);

  int xx = 0;
  int xd = 1;
SpriteInst sprites[10];

int playerSprite = 7;
int smokeSpriteL = 8;
int smokeSpriteR = 9;

float s_camPos = 0;
Car s_car;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  display.begin();
  
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
sprites[smokeSpriteR].flip = true;

}

uint8_t s_skyBlue = 0xf8;
uint8_t s_groundGreen = 0x08;
uint8_t s_darkGrey = 0x49;
uint8_t s_lightGrey = 0xb6;
float roadPos[8] = {0,1,0,-2,0,1,3,0};

float getRoadPosAt(float playerPos)
{
  float normalisedPlayerPos = playerPos / 32;
  int lowerBound = floor(normalisedPlayerPos);
  int upperBound = floor(normalisedPlayerPos+1);
  float amt = normalisedPlayerPos - lowerBound;
  
  return roadPos[lowerBound%8]*(1-amt) + roadPos[upperBound%8]*amt;
}

void drawRoadSection(uint8_t* lineBuffer, float distance, float playerPos, int width, float camPos)
{
  float pos = playerPos + distance;
  memset(lineBuffer, s_groundGreen, 96);
  int pDist = (int)pos;
  uint8_t col = pDist%2 == 0 ? s_darkGrey : s_lightGrey;
  
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
    float pH = 1 - ((float)(lineIndex - 31))/32.0f;
    float distance = (pH*pH) * 12;
    int width = 8 + (lineIndex - 31);
    drawRoadSection(lineBuffer, distance, s_car.zPos, width, s_camPos); 
  }
}

void processScreen()
{
  display.goTo(0,0);
  display.startData();
  
  uint8_t lineBuffer[96];

  
  for(int lines = 0; lines < 64; ++lines)
  {
    memset(lineBuffer,0,96);
    doLine(lineBuffer, lines);
    for(int index = 0; index < 10; ++index)
    {
      if(sprites[index].enabled)
      { 
        const Sprite* spriteType = sprites[index].sprite;
        int curLine = lines - sprites[index].y;
        if ( curLine >= 0 && curLine < spriteType->height-1 )
        {
          for(int x = 0; x < spriteType->width; ++x)
          {
            int tx = x + sprites[index].x;
            if ( tx >= 0 && tx < 96 )
            {
              uint8_t col = sprites[index].flip ? spriteType->data[(spriteType->width-(x+1))+(curLine*spriteType->width)] : spriteType->data[x+(curLine*spriteType->width)];
              if ( col != ALPHA )
              {
                lineBuffer[tx] = col;
              }
            }
          }
        }
      }
    }
    display.writeBuffer(lineBuffer,96);
  }
  
  display.endTransfer();
}


void loop() {
  
  
  s_camPos = (s_car.xPos + getRoadPosAt(s_car.zPos + 6)) / 2;
  // put your main code here, to run repeatedly:
  sprites[playerSprite].x = (48 - 10) - (s_camPos*40) + (s_car.xPos*40);
  sprites[playerSprite].y = 49;
  processScreen();
  getJoystick();
  filterData(50);

  
  s_car.currentSpeed += s_joystickData.RY * 0.001f;
  s_car.currentAngle += s_joystickData.LX * 0.001f;
  
  if ( s_car.currentSpeed > 0.8f )
  {
    s_car.currentSpeed = 0.8f;
  }
  if(s_car.currentSpeed < 0 )
  {
    s_car.currentSpeed = 0;
  }
  s_car.currentSpeed *= 0.9f;
  s_car.currentAngle *= 0.6f;
  
  s_car.xPos += s_car.currentAngle * 0.1f * s_car.currentSpeed;
  
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
    
    sprites[smokeSpriteL].x = (48 - 15) - (s_camPos*40) + (s_car.xPos*40);
    sprites[smokeSpriteL].y = 64-19;
    
    sprites[smokeSpriteR].x = (48 + 2) - (s_camPos*40) + (s_car.xPos*40);
    sprites[smokeSpriteR].y = 64-19;
  }
  else  
  {
    sprites[smokeSpriteL].enabled = false;
    sprites[smokeSpriteR].enabled = false;
  }
}
