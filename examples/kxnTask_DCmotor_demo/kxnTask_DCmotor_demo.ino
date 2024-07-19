#include "Demo1.h"
Demo1 Demo;

void setup(void)
{
    Demo.setup();
}
void loop(void)
{
    kxnTaskManager.run(millis());
}