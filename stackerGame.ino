#define BUTTON_R 12
#include "animations.h" // animations for start screen

// libraries/defines for 8x32 matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
#define CLK_PIN 13
#define DATA_PIN 11
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
  buttonRState = digitalRead(BUTTON_R);
  buttonLState = digitalRead(BUTTON_L);

  // start screen animation setup
  matrixDisplay.begin();
  matrixDisplay.setIntensity(5);
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

  //-----------------------//
  // STATE 1: TITLE SCREEN //
  //-----------------------//

  static uint8_t i = 0;
  bool inGame = false;
  uint8_t diffSelect = 1;

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
    lcd.setCursor(0,0);
    lcd.print("EZ | MED | HARD");
    if (buttonRState == LOW)
    {
      lcd.setCursor(0, 1);
      lcd.print("^");
    }
  }

  //----------------------//
  //   STATE 2: IN-GAME   //
  //----------------------//
  
}

