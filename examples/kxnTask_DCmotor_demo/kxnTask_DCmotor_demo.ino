#include "kxnTask_DCmotor.h"
kxnTask_DCmotor DCmotor;

void setup(void)
{
    DCmotor.setup(5,7,4);
    DCmotor.forward(40);
}
void loop(void)
{
    kxnTaskManager.run(millis());
}