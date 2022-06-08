#include <Servo.h>

// initial pin
Servo myServo;

const int xPin = A0;
const int yPin = A1; // up-0, down-1023
const int motorSwitchPin = 5;
const int servoPin = 9; // For Servo Signal
const int motorEnablePin = 11; // for H-Bridge
const int controlPin1 = 2;
const int controlPin2 = 3; 

int ServoAngle = 0;
int xValue = 0;
int yValue = 0;
int enableValue = 0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;

int motorEnable = 0;
int motorSpeed = 0;
int directionSpeed = 0;
int motorDirection = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(motorSwitchPin, INPUT);
  myServo.attach(servoPin);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);  

  digitalWrite(motorEnablePin, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  ServoAngle = map(xValue, 965, 0, 45, 135);
  myServo.write(ServoAngle);
  delay(15);

  onOffSwitchState = digitalRead(motorSwitchPin);
  delay(1);
  directionSpeed = ( 510 - analogRead(yPin))/ 9;
  motorSpeed = abs(directionSpeed);

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
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
        
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if (motorEnable == 1) {
    analogWrite(motorEnablePin, motorSpeed);
  } else {
    analogWrite(motorEnablePin, 0);
  }
  previousOnOffSwitchState = onOffSwitchState;
  
  Serial.print(" x-value ");
  Serial.print(xValue);
  Serial.print(" y-value ");
  Serial.print(yValue);
  Serial.print(" motorSpeed: ");
  Serial.print(motorSpeed);
  Serial.print(" onOffSwitchState: ");
  Serial.print(onOffSwitchState);
  Serial.print(" directionSwitchState: ");
  Serial.print(directionSwitchState);
  Serial.print(" motorEnable: ");
  Serial.print(motorEnable);
  Serial.print(" motorDirection: ");
  Serial.print(motorDirection);
  Serial.print("\n: ");
}
