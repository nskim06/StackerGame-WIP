#define BUTTON_R 12
#define BUTTON_L 9
#include "animations.h"
#include "game.h"
#include "customFonts.h"

// libraries/defines for 8x32 matrix
#include <LedControl.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define CLK_PIN 13
#define DATA_PIN 11
LedControl lc = LedControl(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola matrixDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// libraries for LCD display
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// variables and constants
#define BUTTON_R 12
#define BUTTON_L 9

void setup() {
 // button setup
  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_L, INPUT);

  // start screen animation setup
  matrixDisplay.begin();
  matrixDisplay.setIntensity(1);
  for (uint8_t i = 0; i < 3; i++)
  {
    animList[i].speed *= matrixDisplay.getSpeed(); 
    animList[i].pause *= 500;
  }

  // lcd screen setup
  lcd.init();
  lcd.backlight();

}

void loop() {

  uint8_t buttonRState = digitalRead(BUTTON_R);
  uint8_t buttonLState = digitalRead(BUTTON_L);

  //-----------------------//
  // STATE 1: TITLE SCREEN //
  //-----------------------//
  
  static uint8_t i = 0;
  bool inGame = false;
  int diff = EASY;
  uint8_t state = 0;

  lcd.setCursor(0,0);
  lcd.print("EZ | MED | HARD");
  lcd.setCursor(0,1);
  lcd.print("^");

  while (!inGame)
  {
    if (matrixDisplay.displayAnimate())
    {
      if (i == 3)
        i = 0;
      matrixDisplay.displayText(animList[i].textout, animList[i].just, animList[i].speed, animList[i].pause, 
      animList[i].anim_in, animList[i].anim_out);
      delay(500);
      i++;
    }

    buttonRState = digitalRead(BUTTON_R);
    buttonLState = digitalRead(BUTTON_L);
    if (buttonRState == LOW) 
      state = 1;
    if (state == 1 && buttonRState == HIGH) {
      lcd.setCursor(diff * 6, 1);
      lcd.print(" ");
      if (diff == HARD) 
        diff = EASY;
      else 
        ++diff;
      lcd.setCursor(diff * 6, 1);
      lcd.print("^");
      state = 0;
    }

    if (buttonLState == LOW)
    {
      delay(1500);
      inGame = true;
    }
  }
  
  // gonna create a cool transition animation here later
  lcd.clear();
  runTransition(matrixDisplay);
  delay(500);

  matrixDisplay.displayClear();
  matrixDisplay.displayShutdown(true);
  SPI.end();
  
  //----------------------//
  //   STATE 2: IN-GAME   //
  //----------------------//
  
  for (uint8_t i = 0; i < 4; ++i)
    {
      lc.shutdown(i, false);
      lc.setIntensity(i, 2);
      lc.clearDisplay(i);
    }

  
  game newGame(diff);
  (newGame.getBlock()).displayBlock(lc);
  delay(500);

  while (inGame) {
    for (int i = 0; i < newGame.getSpeed(); ++i)
    {
      buttonRState = digitalRead(BUTTON_R);
      buttonLState = digitalRead(BUTTON_L);
      if (buttonRState == LOW || buttonLState == LOW)
      {
        delay(1000);
        newGame.setTopBlock(new block(3, random(0, 2), random(1, 7), newGame.getHeight() + 2));
        newGame.setHeight(7 - (newGame.getBlock().get_y()) + (newGame.getBlock().get_address() * 8));   // had to cancel out the "7 -" from get_y() and account for address
        (newGame.getBlock()).displayBlock(lc);
        continue;
      }
      else
        delay(1);
    }
    (newGame.getBlock()).step(lc);

  }

  delay(5000);
}

