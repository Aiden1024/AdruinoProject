#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(A0, A1); // CE, CSN

const byte address[6] = "10101";

// init Pin
// For JoyStick
const int xPin = A0;
const int yPin = A1; // up-0, down-1023

// For H-Bridge POWER
const int motorSwitchPin = 10;
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

String Cmd = "STP";
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

// Helper FB
void FB(int dir) {
  runMotor(BR_Pin1, BR_Pin2, dir);
  runMotor(FR_Pin1, FR_Pin2, dir);
  runMotor(BL_Pin1, BL_Pin2, !dir);
  runMotor(FL_Pin1, FL_Pin2, !dir);
}

void SPIN(int dir) {
  runMotor(BR_Pin1, BR_Pin2, dir);
  runMotor(FR_Pin1, FR_Pin2, dir);
  runMotor(BL_Pin1, BL_Pin2, dir);
  runMotor(FL_Pin1, FL_Pin2, dir);
}


void GFW() {
  FB(1);  
}

void GBW() {
  FB(0);  
}

void LSP() {
  SPIN(1);  
}

void RSP() {
  SPIN(0);  
}

void LFT() {
  runMotor(BR_Pin1, BR_Pin2, 1);
  runMotor(FR_Pin1, FR_Pin2, 1);
  runMotor(BL_Pin1, BL_Pin2, -1);
  runMotor(FL_Pin1, FL_Pin2, -1);
}

void RFT() {
  runMotor(BR_Pin1, BR_Pin2, -1);
  runMotor(FR_Pin1, FR_Pin2, -1);
  runMotor(BL_Pin1, BL_Pin2, 0);
  runMotor(FL_Pin1, FL_Pin2, 0);
}

void LBT() {
  runMotor(BR_Pin1, BR_Pin2, 0);
  runMotor(FR_Pin1, FR_Pin2, 0);
  runMotor(BL_Pin1, BL_Pin2, -1);
  runMotor(FL_Pin1, FL_Pin2, -1);
}

void RBT() {
  runMotor(BR_Pin1, BR_Pin2, -1);
  runMotor(FR_Pin1, FR_Pin2, -1);
  runMotor(BL_Pin1, BL_Pin2, 1);
  runMotor(FL_Pin1, FL_Pin2, 1); 
}

void STP() {
  runMotor(BR_Pin1, BR_Pin2, -1);
  runMotor(FR_Pin1, FR_Pin2, -1);
  runMotor(BL_Pin1, BL_Pin2, -1);
  runMotor(FL_Pin1, FL_Pin2, -1); 
}

void testTurn() {
  if (motorDirection == 1 && turnDirection == 1) {
    LFT();
  } else if (motorDirection == 1 && turnDirection == 0) {
    RFT(); 
  } else if (motorDirection == 0 && turnDirection == 1) {
    LBT();
  } else {
    RBT();
  }
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
  radio.begin();
  radio.openReadingPipe(0, address);
  // radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);	// Debugging only
  
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

  // if (xValue > 450 && xValue < 580 ) {
  //   goFB();
  //   if (motorEnable == 1) {
  //   analogWrite(enablePin, motorSpeed);
  //   } else {
  //     analogWrite(enablePin, 0);
  //   }
  //   Serial.print(" going FW ");
  // } else if (xValue < 15 || xValue > 1009){
  //   goSpin();
  //   if (motorEnable == 1) {
  //   analogWrite(enablePin, absTurnSpeed);
  //   } else {
  //     analogWrite(enablePin, 0);
  //   }
  //   Serial.print(" going Spin ");
  // } else {
  //   goTurn();
  //   if (motorEnable == 1) {
  //   analogWrite(enablePin, motorSpeed);
  //   } else {
  //     analogWrite(enablePin, 0);
  //   }
  //   Serial.print(" going Turn ");
  // }

  if (motorEnable == 1) {
    analogWrite(enablePin, 1023 );
    } else {
      analogWrite(enablePin, 0);
    }
  
  previousOnOffSwitchState = onOffSwitchState;

  // RF Control Moduel
  // Radio
  if (radio.available()) {
    char text[4] = "";
    radio.read(&text, sizeof(text));
    // Serial.println(text);
    Cmd = (char*)text;
    if (Cmd == String("STP")) {
      Serial.print(" STP Block ");   
      STP(); 
      analogWrite(enablePin, 0 );
    } else if (Cmd == String("GFW")) {
      Serial.print(" GFW Block ");   
      GFW();
    } else if (Cmd == String("GBW")) {
      Serial.print(" GBW Block ");   
      GBW();
    } else if (Cmd == String("LSP")) {
      Serial.print(" LSP Block ");   
      LSP();
    } else if (Cmd == String("RSP")) {
      Serial.print(" RSP Block ");   
      RSP();
    } else if (Cmd == String("LFT")) {
      Serial.print(" LFT Block ");   
      LFT();
    } else if (Cmd == String("RFT")) {
      Serial.print(" RFT Block ");   
      RFT();
    } else if (Cmd == String("LBT")) {
      Serial.print(" LBT Block ");   
      LBT();
    } else if (Cmd == String("RBT")) {
      Serial.print(" RBT Block ");   
      RBT();
    } else {
      Serial.println(" Not a Valid Command ");   
    }

    Serial.println();
  }
  
  // uint8_t buf[4];
  // uint8_t buflen = sizeof(buf);
  // if (driver.recv(buf, &buflen)) // Non-blocking
  // {
  //   int i;
  //   // Message with a good checksum received, dump it.
  //   // Serial.print((char*)buf);   
    
  //   Cmd = (char*)buf;
    
  //   if (Cmd == String("STP")) {
  //     Serial.print(" STP Block ");   
  //     STP(); 
  //     analogWrite(enablePin, 0 );
  //   } else if (Cmd == String("GFW")) {
  //     Serial.print(" GFW Block ");   
  //     GFW();
  //   } else if (Cmd == String("GBW")) {
  //     Serial.print(" GBW Block ");   
  //     GBW();
  //   } else if (Cmd == String("LSP")) {
  //     Serial.print(" LSP Block ");   
  //     LSP();
  //   } else if (Cmd == String("RSP")) {
  //     Serial.print(" RSP Block ");   
  //     RSP();
  //   } else if (Cmd == String("LFT")) {
  //     Serial.print(" LFT Block ");   
  //     LFT();
  //   } else if (Cmd == String("RFT")) {
  //     Serial.print(" RFT Block ");   
  //     RFT();
  //   } else if (Cmd == String("LBT")) {
  //     Serial.print(" LBT Block ");   
  //     LBT();
  //   } else if (Cmd == String("RBT")) {
  //     Serial.print(" RBT Block ");   
  //     RBT();
  //   } else {
  //     Serial.println(" Not a Valid Command ");   
  //   }

  //   Serial.println();

  // }     

   
  



  // Serial.print(" x-value ");
  // Serial.print(xValue);
  // Serial.print(" y-value ");
  // Serial.print(yValue);
  // Serial.print(" motorSpeed: ");
  // Serial.print(motorSpeed);
  // Serial.print(" motorEnable: ");
  // Serial.print(motorEnable);
  // Serial.print(" motorDirection: ");
  // Serial.print(motorDirection);
  // Serial.print(" turnDirection: ");
  // Serial.print(turnDirection);
  

  
  // Serial.print("\n: ");
} 
