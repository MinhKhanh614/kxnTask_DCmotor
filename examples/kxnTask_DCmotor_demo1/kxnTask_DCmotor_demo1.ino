#include "khanhTest_kxnTask_DCmotor.h"
kxnTask_DCmotor motor;

unsigned long currentMillis = 0, lastMillis = 0, interval = 1000;
unsigned long thatTimeMillis = 0;
long value1, value2, value3;

void setup()
{
  motor.setup(1, 2, 3, 100);
  // motor.write(-100,5000);
}

void loop()
{
  motor.write(30,3000);
  // kxnTaskManager.run(millis());
  khanhDelay(5000);
}

void khanhDelay(unsigned long Time)
{
  while (millis() <= millis() + Time)
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