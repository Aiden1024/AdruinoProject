// init Pin
// For JoyStick
const int xPin = A0;
const int yPin = A1; // up-0, down-1023

// For H-Bridge POWER
const int motorSwitchPin = 13;
const int enablePin = A5;

// Motor Pins
const int BR_Pin1 = 3;
const int BR_Pin2 = 2; 

const int FR_Pin1 = 5;
const int FR_Pin2 = 4; 

const int FL_Pin1 = 7;
const int FL_Pin2 = 6; 

const int BL_Pin1 = 9;
const int BL_Pin2 = 8; 

// Variables
int xValue = 0;
int yValue = 0;
int motorSpeed = 0;
int directionSpeed = 0;
int motorDirection = 1;
int motorEnable = 0;
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;

// Motor Function

void runMotor(int pin1, int pin2, int direction) {
  if (direction == 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);    
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);       
  }

}

void setup() {
  // put your setup code here, to run once:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(BR_Pin1, OUTPUT);
  pinMode(BR_Pin2, OUTPUT);  
  
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  directionSpeed = ( 510 - analogRead(yPin)) / 2;
  motorSpeed = abs(directionSpeed);

  onOffSwitchState = digitalRead(motorSwitchPin);
  delay(1);
  
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH) {
      motorEnable = !motorEnable;
    }
  }
  
  if (directionSpeed > 0) {
    motorDirection = 1;
  } else {
    motorDirection = 0;    
  }

  if (motorDirection == 1) {
    digitalWrite(BR_Pin1, HIGH);
    digitalWrite(BR_Pin2, LOW);
        
  } else {
    digitalWrite(BR_Pin1, LOW);
    digitalWrite(BR_Pin2, HIGH);
  }

  if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }
  
  previousOnOffSwitchState = onOffSwitchState;

  Serial.print(" x-value ");
  Serial.print(xValue);
  Serial.print(" y-value ");
  Serial.print(yValue);
  Serial.print(" motorSpeed: ");
  Serial.print(motorSpeed);
  Serial.print(" motorEnable: ");
  Serial.print(motorEnable);
  Serial.print(" motorDirection: ");
  Serial.print(motorDirection);
  Serial.print(" BR_Pin1: ");
  Serial.print(digitalRead(BR_Pin1));
  Serial.print(" BR_Pin2: ");
  Serial.print(digitalRead(BR_Pin2));
  
  Serial.print("\n: ");
}
