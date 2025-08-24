#ifndef STACKER_H
#define STACKER_H
#include <MD_Parola.h>
#include "customFonts.h"

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
  {PA_SCROLL_RIGHT, PA_SCROLL_RIGHT, "STACKER", 4, 0, PA_LEFT},
  {PA_RANDOM, PA_GROW_DOWN, "STACKER", 2, 2, PA_CENTER},
  {PA_SCROLL_LEFT, PA_SCROLL_LEFT, "STACKER", 4, 0, PA_CENTER}
};

// use gameFont
animations transition = {PA_SCROLL_LEFT, PA_SCROLL_LEFT, "~~~~", 1, 3, PA_CENTER};

void runTransition(MD_Parola matrixDisplay)
{
  transition.speed *= matrixDisplay.getSpeed(); 
  transition.pause *= 500;
  MD_MAX72XX::fontType_t *pFont = gameFont;
  matrixDisplay.setFont(pFont);
  matrixDisplay.setCharSpacing(0);
  matrixDisplay.displayText(transition.textout, transition.just, transition.speed, transition.pause, transition.anim_in, transition.anim_out);
  while (!matrixDisplay.displayAnimate())
    continue;
  matrixDisplay.setFont(nullptr);
  matrixDisplay.setCharSpacing(1);
  transition.speed /= matrixDisplay.getSpeed();
  transition.pause /= 500;
}

#endif
