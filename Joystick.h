class JoystickData
{
  public:
  int LX = 0;
  int RX = 0;
  int LY = 0;
  int RY = 0;
  bool b1 = false;
  bool b2 = false;
};

JoystickData s_joystickData;

void getJoystick(){
  Wire.requestFrom(0x22,6);
  int data[4];
  for(int i=0;i<4;i++){
    data[i]=Wire.read();
  }
  byte lsb=Wire.read();
  byte buttons=~Wire.read();
  s_joystickData.b1=buttons&4;
  s_joystickData.b2=buttons&8;
  for(int i=0;i<4;i++){
    data[i]<<=2;
    data[i]|= ((lsb>>(i*2))&3);
    data[i]-=511;
  }
  s_joystickData.RX=data[0];
  s_joystickData.RY=-data[1];
  s_joystickData.LX=-data[2];
  s_joystickData.LY=data[3];
}

void filterData(int deadZone)
{
  if (abs(s_joystickData.RX) < deadZone )
  {
    s_joystickData.RX = 0;
  }
    if (abs(s_joystickData.LX) < deadZone )
  {
    s_joystickData.LX = 0;
  }
    if (abs(s_joystickData.RY) < deadZone )
  {
    s_joystickData.RY = 0;
  }
    if (abs(s_joystickData.LY) < deadZone )
  {
    s_joystickData.LY = 0;
  }
}
