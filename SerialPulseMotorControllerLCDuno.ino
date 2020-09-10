#include <SerialCommand.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

#define LED 13        // LED on board

#define dirPin    2
#define pulsePin  3       
#define stepPerRevolution 3200
#define enPin     4       // Enable Pin

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
SerialCommand SCmd;             // The demo SerialCommand object
int prevTime;
int pulseWidthMicros = 300;   //Set delay
int LswitchFow=5;
int LswitchBack=7;
int flag=0;

void setup()
{
  pinMode(LED,OUTPUT);            // Configure the onboard LED for output
  digitalWrite(LED,LOW);          // default to LED off
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
  pinMode(pulsePin,OUTPUT);
  digitalWrite(pulsePin,HIGH);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,HIGH);
  pinMode(LswitchFow, INPUT);
  pinMode(LswitchBack, INPUT);  

  Serial.begin(9600); 

  // Setup callbacks for SerialCommand commands 
  SCmd.addCommand("F",moveForwardCommand);   
  SCmd.addCommand("B",moveBackwardCommand);    
  SCmd.addCommand("H",homeCommand);       
  SCmd.setDefaultHandler(unrecognized);   // Handler for command that isn't matched 

  
  lcd.begin(20, 4); // initialize the lcd

  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dir   : ");
  lcd.setCursor(0, 1);
  lcd.print("Pulse : ");

  //phDelay = 1;
 // plDelay = 9;
  prevTime = millis();
}

void loop()
{  
  SCmd.readSerial();
}


void moveForwardCommand()    
{
  int aNumber;  
  char *arg; 

  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    lcd.setCursor(8, 0);
    lcd.print("F");
    lcd.setCursor(8, 1);
    //lcd.print(aNumber);
    digitalWrite(dirPin,LOW);
    for (int i = 0; i < aNumber; i++) {
      digitalWrite(pulsePin,LOW);
      delayMicroseconds(pulseWidthMicros);
      digitalWrite(pulsePin,HIGH);
      delayMicroseconds(pulseWidthMicros);
      if (digitalRead(LswitchFow) == LOW) 
        {
            digitalWrite(pulsePin,LOW);
            delayMicroseconds(pulseWidthMicros);
            digitalWrite(pulsePin,LOW);
        }    
     }
     delay(2000);
       digitalWrite(dirPin,HIGH);
       for (int i = 0; i < aNumber; i++) {
       digitalWrite(pulsePin,LOW);
       delayMicroseconds(pulseWidthMicros);
       digitalWrite(pulsePin,HIGH);
       delayMicroseconds(pulseWidthMicros); 
      }
    }
}

void moveBackwardCommand()    
{
  int aNumber;  
  char *arg; 

  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    lcd.setCursor(8, 0);
    lcd.print("B");
    lcd.setCursor(8, 1);
   // lcd.print(aNumber);
    digitalWrite(dirPin,HIGH);
    for (int i = 0; i < aNumber; i++) {
      digitalWrite(pulsePin,LOW);
      delayMicroseconds(pulseWidthMicros);
      digitalWrite(pulsePin,HIGH);
      delayMicroseconds(pulseWidthMicros);
      if (digitalRead(LswitchBack) == LOW) 
        {
            digitalWrite(pulsePin,LOW);
            delayMicroseconds(pulseWidthMicros);
            digitalWrite(pulsePin,LOW);
        }
     }
  } 
}


void homeCommand()    
{
  lcd.setCursor(8, 0);
  lcd.print(" ");
  lcd.setCursor(8, 1);
  lcd.print("       ");
}



// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
  
}
