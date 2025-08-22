#define BUTTON_R 12

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
int screenTimer = 3;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  matrixDisplay.begin();
  matrixDisplay.setIntensity(0);
  matrixDisplay.displayClear();
  matrixDisplay.print("STACKER");
}

void loop() {

  lcd.setCursor(0,0);
  lcd.print("Pick Difficulty");

  while (screenTimer >= 0)
  {
    lcd.setCursor(0, 1);
    lcd.print(screenTimer);
    delay(1000);
    --screenTimer;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EZ | MED | HARD");

  delay(3000);
}

