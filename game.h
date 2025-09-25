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
  unsigned int m_x;       // position of leftmost column of block, from -3 to 7
  unsigned int m_y;       // use integer division for later
  unsigned int m_address;
public:
  block(int speed, int length, bool goingRight, int x, int y)
    : m_speed(speed), m_length(length), m_goingRight(goingRight), m_x(x), m_y(y) 
    {}

  void setX(int newX) {
    m_x = newX;
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
      if (get_x() - i > 7)
        continue;
      lc.setLed(get_address(), get_x() - i, get_y(), true);
      lc.setLed(get_address(), get_x() - i, get_y() - 1, true);
    }
  }
  void step(LedControl lc) {
    if (getDir()) {
      if (get_x() == 0) {   // block is at the RIGHT edge of display
        setDir(!getDir());  
        return;
      }  
      lc.setLed(get_address(), get_x(), get_y(), false);
      lc.setLed(get_address(), get_x(), get_y() - 1, false);
      lc.setLed(get_address(), get_x() - getLen(), get_y(), true);    // no edge-checking, but still works
      lc.setLed(get_address(), get_x() - getLen(), get_y() - 1, true);
      setX(8 - get_x());
      return;
    }
    else {
      if (get_x() == 10) {   // block is at the LEFT edge of display
        setDir(!getDir());  
        return;
      }  
      uint8_t x_right = get_x() - getLen() + 1;
      lc.setLed(get_address(), x_right, get_y(), false);
      lc.setLed(get_address(), x_right, get_y() - 1, false);
      lc.setLed(get_address(), get_x() + 1, get_y(), true);    // no edge-checking, but still works
      lc.setLed(get_address(), get_x() + 1, get_y() - 1, true);
      setX(6 - get_x());
      return;
    }
    
      
  }
};
  // one "step" in the block's animation


#endif