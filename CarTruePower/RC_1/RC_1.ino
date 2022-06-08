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

int turnDirection = 0;
int turnSpeed = 0;
int absTurnSpeed = 0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;

// Motor Function

void runMotor(int pin1, int pin2, int direction) {
  if (direction == 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);    
  } else if (direction == 1) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);       
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);  
  }

}

void goFB() {
  runMotor(BR_Pin1, BR_Pin2, motorDirection);
  runMotor(FR_Pin1, FR_Pin2, motorDirection);
  runMotor(BL_Pin1, BL_Pin2, !motorDirection);
  runMotor(FL_Pin1, FL_Pin2, !motorDirection);
}

void goTurn() {
  if (motorDirection == 1 && turnDirection == 1) {
    runMotor(BR_Pin1, BR_Pin2, motorDirection);
    runMotor(FR_Pin1, FR_Pin2, motorDirection);
    runMotor(BL_Pin1, BL_Pin2, -1);
    runMotor(FL_Pin1, FL_Pin2, -1);
  } else if (motorDirection == 1 && turnDirection == 0) {
    runMotor(BR_Pin1, BR_Pin2, -1);
    runMotor(FR_Pin1, FR_Pin2, -1);
    runMotor(BL_Pin1, BL_Pin2, !motorDirection);
    runMotor(FL_Pin1, FL_Pin2, !motorDirection);    
  } else if (motorDirection == 0 && turnDirection == 1) {
    runMotor(BR_Pin1, BR_Pin2, motorDirection);
    runMotor(FR_Pin1, FR_Pin2, motorDirection);
    runMotor(BL_Pin1, BL_Pin2, -1);
    runMotor(FL_Pin1, FL_Pin2, -1);
     
  } else {
    runMotor(BR_Pin1, BR_Pin2, -1);
    runMotor(FR_Pin1, FR_Pin2, -1);
    runMotor(BL_Pin1, BL_Pin2, !motorDirection);
    runMotor(FL_Pin1, FL_Pin2, !motorDirection); 
  }
  
}

void goSpin() {
  runMotor(BR_Pin1, BR_Pin2, turnDirection);
  runMotor(FR_Pin1, FR_Pin2, turnDirection);
  runMotor(BL_Pin1, BL_Pin2, turnDirection);
  runMotor(FL_Pin1, FL_Pin2, turnDirection);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(BR_Pin1, OUTPUT);
  pinMode(BR_Pin2, OUTPUT);  
  pinMode(FR_Pin1, OUTPUT);
  pinMode(FR_Pin2, OUTPUT);  
  pinMode(FL_Pin1, OUTPUT);
  pinMode(FL_Pin2, OUTPUT);  
  pinMode(BL_Pin1, OUTPUT);
  pinMode(BL_Pin2, OUTPUT);  
  
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  directionSpeed = ( 510 - analogRead(yPin));
  motorSpeed = abs(directionSpeed);

  turnSpeed = ( 510 - analogRead(xPin));
  absTurnSpeed = abs(turnSpeed);

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

  if (turnSpeed > 0) {
    turnDirection = 1;
  } else {
    turnDirection = 0;    
  }

  if (xValue > 450 && xValue < 580 ) {
    goFB();
    if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
    } else {
      analogWrite(enablePin, 0);
    }
    Serial.print(" going FW ");
  } else if (xValue < 15 || xValue > 1009){
    goSpin();
    if (motorEnable == 1) {
    analogWrite(enablePin, absTurnSpeed);
    } else {
      analogWrite(enablePin, 0);
    }
    Serial.print(" going Spin ");
  } else {
    goTurn();
    if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
    } else {
      analogWrite(enablePin, 0);
    }
    Serial.print(" going Turn ");
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
  Serial.print(" turnDirection: ");
  Serial.print(turnDirection);
  

  
  Serial.print("\n: ");
}
