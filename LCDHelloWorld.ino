
#include <Adafruit_LiquidCrystal.h>

#include <Wire.h>

Adafruit_LiquidCrystal lcd(0);

void setup() 
{
 lcd.begin(16,2);
 lcd.print("Hello World!");
 lcd.setCursor (7,1);
 lcd.print(":)");
}

void loop() 
{
 //nothing
}
