const int button = 2;
int val = 0;

#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>
Adafruit_LiquidCrystal lcd(0);

void setup() 
{
 pinMode(button, INPUT);
 lcd.begin(16,2);
 
 val = digitalRead(button);
 
 if(val == HIGH)
 {
   lcd.print("Hello World!"); 
   return;
 }
 else
 {
   lcd.print("_");
   return;
 }
}


void loop()
{
 
 
 
}
