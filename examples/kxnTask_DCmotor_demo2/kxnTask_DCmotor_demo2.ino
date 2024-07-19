#include "kxnTask_DCmotor.h"
kxnTask_DCmotor dcmotor;
void setup()
{
    dcmotor.setup(5,7,4);
    // dcmotor.write(40);
    dcmotor.write_for(40,10000);
}
void loop(){
    kxnTaskManager.run(millis());
}