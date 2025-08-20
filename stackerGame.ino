// libraries/defines for 8x32 matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// libraries for LCD display
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.displayClear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("wassup");

  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.print("I Like");

  delay(3000);
}
