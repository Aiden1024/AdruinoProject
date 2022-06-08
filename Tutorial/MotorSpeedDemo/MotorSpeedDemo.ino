const int controlPin1 =2;
const int controlPin2 =3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;
// states status

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

// speed
int motorEnable = 0;
int motorSpeed = 0;
int motorDirection = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin) / 4;

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
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH) {
      motorEnable = !motorEnable;
    }
  }

  if (directionSwitchState != previousDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
        
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }


  if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }


  previousOnOffSwitchState = onOffSwitchState;

  previousDirectionSwitchState = directionSwitchState;
}
