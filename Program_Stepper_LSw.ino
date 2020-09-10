// testing a stepper motor with a Pololu A4988 driver board or equivalent
// on an Uno the onboard led will flash with each step
// this version uses delay() to manage timing

#define ledPin 13        // LED on board
#define dirPin    2
#define pulsePin  3  
#define stepPerRevolution 3200
int LswitchFow=5;
//int pulseWidthMicros = 300;  // microseconds
int millisbetweenSteps = 250; // milliseconds - or try 1000 for slower steps


void setup() {

  Serial.begin(9600);
  Serial.println("Starting StepperTest");
  digitalWrite(ledPin, LOW);
  
  delay(2000);

  pinMode(dirPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(LswitchFow, INPUT);
 
  digitalWrite(dirPin, LOW);
  for(int n = 0; n < stepPerRevolution; n++) {
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(300); // this line is probably unnecessary
    digitalWrite(pulsePin, LOW);
       if (digitalRead(LswitchFow) == LOW)
    delay(millisbetweenSteps);
    
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
  
  delay(2000);
  

  digitalWrite(dirPin, HIGH);
  for(int n = 0; n < stepPerRevolution; n++) {
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(300); // probably not needed
    digitalWrite(pulsePin, LOW);
    
    delay(millisbetweenSteps);
    
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void loop() {
  
}
