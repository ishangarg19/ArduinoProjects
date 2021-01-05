#include <LiquidCrystal.h>
#include <Keypad.h>

#define buzzer 8
#define trigPin 9
#define echoPin 10

LiquidCrystal lcd(12, 11, 2,3,4,5);
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {14,15,16,17};
byte colPins[COLS] = {18,19,20,21};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);
char customKey = customKeypad.getKey();
char menuKey = customKeypad.getKey();
char newKey = customKeypad.getKey();

byte cursorPos = 4;
const int pinSize = 6;
byte charEntered = 0;
char menuOption[3] = {'A','B','C'};

int distance, initialDistance, currentDistance, i;
long duration;

char digits[6] = {'1','6','4','7','0','9'};
        
char digit1Ans;
char digit2Ans;
char digit3Ans;
char digit4Ans;
char digit5Ans;
char digit6Ans;

char digit1New;
char digit2New;
char digit3New;
char digit4New;
char digit5New;
char digit6New;

bool digit1 = false;
bool digit2 = false;
bool digit3 = false;
bool digit4 = false;
bool digit5 = false;
bool digit6 = false;

bool correct = false;
bool changePin = false;
bool start = true;
bool enterNewPin = true;
bool runNewKey = true;
bool alarm = false;
bool alarmActivated = false;

void setup()
{
  lcd.begin(16,2);
  lcd.print("Ishan's");
  lcd.setCursor(0,1);
  lcd.print("Vault");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
  delay(1000);
  lcd.clear();

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop()
{
  
  startup();
  if(alarmActivated == true)
  {
    activateAlarm();
  }
  if(runNewKey == false)
  {
    pinInput();
  }
  if(alarm == true)
  {
    tone(buzzer, 100, 1000);
    
  }
}

void startup()
{
  if(start == true)
  { 
    lcd.setCursor(0,0);
    lcd.print("A-Activate");
    lcd.setCursor(0,1);
    lcd.print("B-Change PIN");
  
  menuKey = customKeypad.getKey();
  if(menuKey)
  {
    if(menuKey == menuOption[0])
    {
      lcd.clear();
      
      digit1Ans = digits[0];
      digit2Ans = digits[1];
      digit3Ans = digits[2];
      digit4Ans = digits[3];
      digit5Ans = digits[4];
      digit6Ans = digits[5];
      
      initialDistance = getDistance();
      start = false;
      runNewKey = false;
      correct = false;
      changePin = false;
      alarmActivated = true;
      
    }
    else if(menuKey == menuOption[1])
    {
      correct = false;
      if(changePin == false)
      {
        
        digit1Ans = digits[0];
        digit2Ans = digits[1];
        digit3Ans = digits[2];
        digit4Ans = digits[3];
        digit5Ans = digits[4];
        digit6Ans = digits[5];
        start = false;
      }
      changePin = true;
      runNewKey = true;
      
      lcd.clear();
    }
//    else if(menuKey == menuOption[2]) ///////////////////////CHANGE SO THAT IT ONLY RUNS IF ALARM IS ON//////////////////////////
//    {
//      
//      digit1Ans = digits[0];
//      digit2Ans = digits[1];
//      digit3Ans = digits[2];
//      digit4Ans = digits[3];
//      digit5Ans = digits[4];
//      digit6Ans = digits[5];
//      
//      lcd.clear();
//      start = false;
//      runNewKey = false;
//    }
   }
  }
  if(start == false && runNewKey == true)
  {
    if(correct == false)
    {
      pinInput();
    }
    if(correct == true)
    {
      newPin();
    }
  }
}

void newPin()
{
  if(runNewKey == true)
  {
    if(changePin == true)
    {
      
      lcd.setCursor(0,0);
      lcd.print("Enter your new");
      lcd.setCursor(0,1);
      lcd.print("PIN:");
    }
  
    newKey = customKeypad.getKey();
    if(newKey)
    {
      lcd.setCursor(cursorPos,1);
      lcd.print(newKey);
      cursorPos++;
      charEntered++;
  
      if(newKey && charEntered == 1)
      {
        digit1New = newKey;
      }
      else if(newKey && charEntered == 2)
      {
        digit2New = newKey;
      }
      else if(newKey && charEntered == 3)
      {
        digit3New = newKey;
      }
      else if(newKey && charEntered == 4)
      {
        digit4New = newKey;
      }
      else if(newKey && charEntered == 5)
      {
        digit5New = newKey;
      }
      else if(newKey && charEntered == 6)
      {
        digit6New = newKey;
      }
  
      if(charEntered == 6)
      {
        cursorPos = 4;
        charEntered = 0;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Your PIN has");
        lcd.setCursor(0,1);
        lcd.print("been changed");
        delay(1000);

        digits[0] = digit1New;
        digits[1] = digit2New;
        digits[2] = digit3New;
        digits[3] = digit4New;
        digits[4] = digit5New;
        digits[5] = digit6New;
        
        digit1Ans = digits[0];
        digit2Ans = digits[1];
        digit3Ans = digits[2];
        digit4Ans = digits[3];
        digit5Ans = digits[4];
        digit6Ans = digits[5];
        lcd.clear();
        
        correct = false;
        start = true;
//        runNewKey = false;
        startup();
      }
      
      changePin = false;
    }
  }    
}

void pinInput()
{
  
  
  if(correct == false)
  {
    
    lcd.setCursor(0,0);
    lcd.print("Please Enter The");
    lcd.setCursor(0,1);
    lcd.print("PIN:");
  }
  
  customKey = customKeypad.getKey();
  if(customKey)
  {
    lcd.setCursor(cursorPos,1);
    lcd.print(customKey);
    cursorPos++;
    charEntered++;

    checkAns();
  }
}

void checkAns()
{
  if(customKey == digit1Ans && charEntered == 1)
    {
      digit1 = true;
    }
    else if(customKey == digit2Ans && charEntered == 2)
    {
      digit2 = true;
    }
    else if(customKey == digit3Ans && charEntered == 3)
    {
      digit3 = true;
    }
    else if(customKey == digit4Ans && charEntered == 4)
    {
      digit4 = true;
    }
    else if(customKey == digit5Ans && charEntered == 5)
    {
      digit5 = true;
    }
    else if(customKey == digit6Ans && charEntered == 6)
    {
      digit6 = true;
    }
    
    if(charEntered == pinSize)
    {
      lcd.clear();
      
      if(digit1==true && digit2==true && digit3==true && digit4==true && digit5==true && digit6==true)
      {
        alarm = false;
        alarmActivated = false;
        lcd.setCursor(0,0);
        lcd.print("Correct!");
        correct = true;
        delay(3000);
        lcd.clear();
        cursorPos = 4;
        charEntered = 0;
        digit1 = false;
        digit2 = false;
        digit3 = false;
        digit4 = false;
        digit5 = false;
        digit6 = false;
       
        
        if (changePin == false)
        {
          start = true;
          startup();
        }
      }
      
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Incorrect.");
        delay(1500);
        cursorPos = 4;
        charEntered = 0;
        digit1 = false;
        digit2 = false;
        digit3 = false;
        digit4 = false;
        digit5 = false;
        digit6 = false;

        if(alarm = true)
        {
          pinInput();
          start = false;
        }
        else if (changePin == false)
        {
          start = true;
          startup();
        }
      }
    }
}

void activateAlarm()
{
  currentDistance = getDistance() + 10;
  
  if (currentDistance < initialDistance) 
  {
    alarm = true; 
  }
}

long getDistance()
{
  //int i=10;
  
  //while( i<=10 ) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  //sumDistance += distance;
  //}
  //int averageDistance= sumDistance/10;
  return distance;
}
