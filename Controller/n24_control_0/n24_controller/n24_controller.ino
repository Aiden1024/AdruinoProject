/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// joy stick pin
const int LxPin = A2;
const int LyPin = A3;
const int RxPin = A0;
const int RyPin = A1;

//

int LxValue = 0;
int LyValue = 0;

int RxValue = 0;
int RyValue = 0;

String sendStatus = "STP";


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "10101";

void setup() {
  pinMode(LxPin, INPUT);
  pinMode(LyPin, INPUT);
  pinMode(RxPin, INPUT);
  pinMode(RyPin, INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  // radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
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

  RxValue = analogRead(RxPin);
  RyValue = analogRead(RyPin);

  // Radio Sec
  char charData[4];
  sendStatus.toCharArray(charData, 4);
  radio.write(&charData, sizeof(charData));
  delay(10);
}