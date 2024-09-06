#include "khanhTest_kxnTask_DCmotor.h"
kxnTask_DCmotor motor;

unsigned long currentMillis = 0, lastMillis = 0, interval = 1000;
unsigned long thatTimeMillis = 0;
long value1, value2, value3;

void setup()
{
  Serial.begin(9600);
  motor.setup(4, 7, 5, 100);
  // motor.write(-100,5000);
}

void loop()
{
  Serial.println(millis());
  // testSerial();
  // motor.write(value1,value2);
  // kxnTaskManager.run(millis());
  // delay(5000);
  khanhDelay(5000);
}

void khanhDelay(unsigned long Time)
{
  while (millis() <= millis() + Time - 1000)
  {
    kxnTaskManager.run(millis());
    currentMillis = millis();
    if (currentMillis - lastMillis >= interval)
    {
      lastMillis = millis();
      
      Time -= 1000;

      if (Time < 0)
        Time = 0;
    }
  }
}
void testSerial()
{
    if (Serial.available())
    {
        String inputText = Serial.readStringUntil('\n');
        sscanf(inputText.c_str(), "%ld %ld %ld", &value1, &value2, &value3);
    }
}