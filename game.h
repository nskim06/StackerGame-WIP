#ifndef GAME_H
#define GAME_H

#include <LedControl.h>

enum difficulty : uint8_t {
  EASY = 0, MEDIUM, HARD
};

class block
{
private:
  unsigned int m_speed;
  unsigned int m_length;  
  bool m_goingRight;      // direction where true = right, false = left
  unsigned int m_x;
  unsigned int m_y;       // use integer division for later
  unsigned int m_address;
public:
  block(int speed, int length, bool goingRight, int x, int y)
    : m_speed(speed), m_length(length), m_goingRight(goingRight), m_x(x), m_y(y) 
    {}

  void setLen(int newLen) {
    m_length = newLen;
  }
  void setDir(bool newDir) {
    m_goingRight = newDir;
  }

  int getLen() {
    return m_length;
  }
  int getDir() {
    return m_goingRight;
  }
  int get_x() {
    return 7 - m_x;   // due to vertical orientation of matrix displays
  }
  int get_y() {
    return 7 - m_y;   // due to vertical orientation of matrix displays
  }
  int get_address() {
    return m_address;
  }
  
  void displayBlock(LedControl lc) {
    for (int i = 0; i < getLen() && (get_x() - i >= 0); ++i)
    {
      lc.setLed(get_address(), get_x() - i, get_y(), true);
      lc.setLed(get_address(), get_x() - i, get_y() - 1, true);
    }
  }
  void step();
};
  // one "step" in the block's animation


#endif