class Sprite
{
  public:
  int width;
  int height;
  const uint8_t* data;
};

class SpriteInst
{
  public:
  const Sprite* sprite = 0;
  int x = 0;
  int y = 0;
  bool enabled = false;
  bool flipX = false;
  bool flipY = false;
};
