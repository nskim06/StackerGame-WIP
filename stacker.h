#ifndef STACKER_H
#define STACKER_H

struct animations
{
  textEffect_t anim_in;
  textEffect_t anim_out;
  const char* textout;
  uint16_t speed;
  uint16_t pause;
  textPosition_t just;
};

animations animList[] = 
{
  {PA_SCROLL_LEFT, PA_SCROLL_LEFT, "WELCOME", 4, 0, PA_LEFT},
  {PA_SLICE, PA_GROW_DOWN, "TO", 3, 2, PA_CENTER},
  {PA_RANDOM, PA_GROW_DOWN, "STACKER", 2, 2, PA_CENTER}
};

#endif STACKER_H
