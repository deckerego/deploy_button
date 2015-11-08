
#include "TrinketFakeUsbSerial.h"

int GREEN_LED = 2;
int YELLOW_LED = 1;
long POWER_SAVE = 30000;
long last_done = millis();

void setup()
{
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(0, INPUT);
  analogWrite(YELLOW_LED, 0);
  analogWrite(GREEN_LED, 0);
  digitalWrite(0, HIGH);
  TFUSerial.begin();
}

void loop()
{
  TFUSerial.task();
  if (! digitalRead(0)) {
    analogWrite(GREEN_LED, 0);

    for(int i = 64; i > 0; --i) {
      TFUSerial.println(1023);
      analogWrite(YELLOW_LED, 32 * (i % 32));
    }

    analogWrite(GREEN_LED, 1023);
    last_done = millis();
    
  } else {
    TFUSerial.println(0);
    analogWrite(YELLOW_LED, 0);
    if(last_done + POWER_SAVE < millis())
      analogWrite(GREEN_LED, 0);
  }
}
