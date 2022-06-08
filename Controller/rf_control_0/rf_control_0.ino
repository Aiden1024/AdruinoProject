#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const int LxPin = A2;
const int LyPin = A3;
const int RxPin = A0;
const int RyPin = A1;

const int LswPin = 2;
const int RswPin = 3;

//

int LxValue = 0;
int LyValue = 0;
int LswValue = 0;

int RxValue = 0;
int RyValue = 0;
int RswValue = 0;

String sendStatus = "STP";

RH_ASK driver;
int test = 0;
void setup()
{
  pinMode(LxPin, INPUT);
  pinMode(LyPin, INPUT);
  pinMode(RxPin, INPUT);
  pinMode(RyPin, INPUT);
  pinMode(LswPin, INPUT);
  pinMode(RswPin, INPUT);

  Serial.begin(19200);	  // Debugging only
  if (!driver.init())
        Serial.println("init failed");
}

void loop()
{
    // int tmp = 512;
    // String stringOne = String(LxValue);
    // char charBuf[5];
    // stringOne.toCharArray(charBuf, 5);
    char charData[4];
    sendStatus.toCharArray(charData, 4);
    // const char *msg = "hello";
    driver.send((uint8_t *)charData, strlen(charData));


  // 450 - 550 stp

  if (LyValue < 450) {
    if (RxValue < 450) {
      sendStatus = "LFT";
    } else if (RxValue > 550) {
      sendStatus = "RFT";
    } else {
      sendStatus = "GFW";
    }

  } else if (LyValue > 550) {
    if (RxValue < 450) {
      sendStatus = "LBT";
    } else if (RxValue > 550) {
      sendStatus = "RBT";
    } else {
      sendStatus = "GBW";
    }
  } else if (LxValue < 450){
    sendStatus = "LSP";
  } else if (LxValue > 550) {
    sendStatus = "RSP";
  } else {
    sendStatus = "STP";
  }

  LxValue = analogRead(LxPin);
  LyValue = analogRead(LyPin);
  LswValue = digitalRead(LswPin);

  RxValue = analogRead(RxPin);
  RyValue = analogRead(RyPin);
  RswValue = digitalRead(RswPin);

  // Serial.print(" LxValue ");
  // Serial.print(LxValue);
  // Serial.print(" LyValue ");
  // Serial.print(LyValue);
  // Serial.print(" LswValue ");
  // Serial.print(LswValue);

  // Serial.print(" RxValue ");
  // Serial.print(RxValue);
  // Serial.print(" RyValue ");
  // Serial.print(RyValue);
  // Serial.print(" RswValue ");
  // Serial.print(RswValue);
  // Serial.print(" sendStatus ");
  // Serial.print(sendStatus);



  // Serial.print(" \n ");
      
}