#ifndef GAME_H
#define GAME_H

#include <LedControl.h>

enum difficulty : int {
  EASY = 0, MEDIUM , HARD
};

class block
{
private:
  unsigned int m_length;  
  bool m_goingRight;      // direction where true = right, false = left
  int m_x;                // position of leftmost column of block, from -3 to 7
  unsigned int m_y;       // position of bottom of block, ranging from 0 to 6 (7, technically)
  unsigned int m_address;
public:
  block() 
    : m_length(3), m_goingRight(true), m_x(0), m_y(0) {m_address = m_y/8; m_y = (m_y - (m_address*8));}

  block(int length, bool goingRight, int x, int y)
    : m_length(length), m_goingRight(goingRight), m_x(x), m_y(y) {m_address = m_y/8; m_y = (m_y - (m_address*8));}

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
  
  void displayBlock(LedControl& lc) {
    for (int i = 0; i < getLen() && (get_x() - i >= 0); ++i)
    {
      if (get_x() - i > 7)
        continue;
      lc.setLed(get_address(), get_x() - i, get_y(), true);
      lc.setLed(get_address(), get_x() - i, get_y() - 1, true);
    }
  }
  void step(LedControl& lc) {   // one "step" in the block's animation
    if (getDir()) {
      if (get_x() == 1) {   // block is one before the RIGHT edge of display, will take one more step before changing dir
        setDir(!getDir());  
      }  
      lc.setLed(get_address(), get_x(), get_y(), false);
      lc.setLed(get_address(), get_x(), get_y() - 1, false);
      lc.setLed(get_address(), get_x() - getLen(), get_y(), true);    // no edge-checking, but still works
      lc.setLed(get_address(), get_x() - getLen(), get_y() - 1, true);
      setX(8 - get_x());
      return;
    }
    else {
      uint8_t x_right = get_x() - getLen() + 1;
      if (x_right == 6) {   // block is one before the LEFT edge of display
        setDir(!getDir());  
      }   
      lc.setLed(get_address(), x_right, get_y(), false);
      lc.setLed(get_address(), x_right, get_y() - 1, false);
      lc.setLed(get_address(), get_x() + 1, get_y(), true);    // no edge-checking, but still works
      lc.setLed(get_address(), get_x() + 1, get_y() - 1, true);
      setX(6 - get_x());
      return;
    }
    
      
  }
};

class game 
{
private:
  unsigned int m_boundaries[2];  // 0-index is left boundary, inclusive
  block* m_topBlock;
  unsigned int m_height;
  unsigned int m_minorPrize;
  unsigned int m_majorPrize;
  int m_gameSpeed;
public:
  game()
    : m_boundaries{0, 7}, m_topBlock(new block()), m_height(0),  m_minorPrize(22), m_majorPrize(30), m_gameSpeed(500) {}
  game(block startBlock)
    : m_boundaries{0, 7}, m_topBlock(&startBlock), m_height(startBlock.get_y()), m_minorPrize(22), m_majorPrize(30), m_gameSpeed(500) {}
  game (int difficulty)
    : m_boundaries{0, 7}, m_height(0), m_minorPrize(22), m_majorPrize(30), m_gameSpeed(500) 
    {
      if (difficulty == EASY) {
        m_topBlock = new block(4, random(0, 2), random(0, 8), 0);
        setSpeed(100);
      }
      else if (difficulty == MEDIUM) {
        m_topBlock = new block(3, random(0, 2), random(0, 8), 0);
        setSpeed(50);
      }
      else if (difficulty == HARD) {
        m_topBlock = new block(3, random(0, 2), random(0, 8), 0);
        setSpeed(35);
      }
    }

  int getHeight() {
    return m_height;
  }
  void getBounds(int (&bounds)[2]) {
    unsigned int i = 0;
    while (i < 2) {
       bounds[i] = m_boundaries[i];
       ++i;
    }
  }
  int getSpeed() {
    return m_gameSpeed;
  }
  block& getBlock() {
    return *m_topBlock;
  }
  
  void setHeight(int height) {
    m_height = height;
  }
  void setBounds(int newBounds[2]) {
    unsigned int i = 0;
    while (i < 2) {
       m_boundaries[i] = newBounds[i];
       ++i;
    }
  }
  void setSpeed(int newSpeed) {
    m_gameSpeed = newSpeed;
  }
  void setTopBlock(block* nextBlock) {
    delete m_topBlock; 
    m_topBlock = nextBlock;
  }

  /*void gameSetup(int difficulty) {
    if (difficulty == EASY) {
      block startBlock = block(4, random(1), random(0, 7), 0);
      setSpeed(800);
      setTopBlock(startBlock);
    }
    else if (difficulty == MEDIUM) {
      block startBlock = block(3, random(1), random(0, 7), 0);
      setSpeed(500);
      setTopBlock(startBlock);
    }
    else if (difficulty == HARD) {
      block startBlock = block(3, random(1), random(0, 7), 0);
      setSpeed(200);
      setTopBlock(startBlock);
    }
  }*/

};
  


#endif