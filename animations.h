#ifndef STACKER_H
#define STACKER_H
#include <MD_Parola.h>

struct animations
{
  textEffect_t anim_in;
  textEffect_t anim_out;
  const char* textout;
  uint16_t speed;
  uint16_t pause;
  textPosition_t just;
};

animations animList[]= 
{
  {PA_SCROLL_RIGHT, PA_SCROLL_RIGHT, "WELCOME", 4, 0, PA_LEFT},
  {PA_RANDOM, PA_GROW_DOWN, "TO", 2, 2, PA_CENTER},
  {PA_SCROLL_LEFT, PA_SCROLL_LEFT, "STACKER", 4, 0, PA_CENTER}
};


#endif STACKER_H
