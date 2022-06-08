#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
int test = 0;
void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    test++;
    char *msg = "Hi you again ?????";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(15);
}