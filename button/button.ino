
#include "TrinketFakeUsbSerial.h"

void setup()
{
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);
  analogWrite(1, 0);
  analogWrite(2, 0);
  digitalWrite(0, HIGH);
  TFUSerial.begin();
}

void loop()
{
  TFUSerial.task();
  if (! digitalRead(0)) {
    analogWrite(2, 0);

    for(int i = 64; i > 0; --i) {
      TFUSerial.println(1023);
      analogWrite(1, 32 * (i % 32));
      delay(50);
    }

    analogWrite(2, 1023);
    
  } else {
    TFUSerial.println(0);
    analogWrite(1, 0);
  }
}
