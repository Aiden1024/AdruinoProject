// init Pin

const int xPin = A0;
const int yPin = A1; // up-0, down-1023
const int PushSwitchPin = 13;
const int enableBLPin = A2;
const int controlPin1 = 2;
const int controlPin2 = 3; 


int xValue = 0;
int yValue = 0;
int motorSpeed = 0;
int directionSpeed = 0;
int motorDirection = 1;
int motorEnable = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(enableBLPin, OUTPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);  
  
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  directionSpeed = ( 510 - analogRead(yPin)) / 2;
  motorSpeed = abs(directionSpeed);
  
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
    analogWrite(enableBLPin, motorSpeed);
  } else {
    analogWrite(enableBLPin, 0);
  }
  
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
  Serial.print(" controlPin1: ");
  Serial.print(digitalRead(controlPin1));
  Serial.print(" controlPin2: ");
  Serial.print(digitalRead(controlPin2));
  
  Serial.print("\n: ");
}
