#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int angle;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  angle = map(potVal, 0, 1023, 0, 179);


  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print("angle: ");
  Serial.print(angle);
  Serial.print("\n");

  myServo.write(angle);
  delay(15);
}
