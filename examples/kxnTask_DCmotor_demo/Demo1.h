#ifndef Demo1_h
#define Demo1_h
#include "kxnTask_DCmotor.h"

DEFINE_TASK_STATE(Demo1){
    Demo1_fw1,
    Demo1_fw2,
    Demo1_tL,
    Demo1_tR,
    Demo1_bw,
    Demo1_stop1,
    Demo1_stop2,
    Demo1_stop3,
    Demo1_stop4,
    Demo1_stop5,

};

CREATE_TASK(Demo1)

kxnTask_DCmotor kxnTask_DCmotor1;
kxnTask_DCmotor kxnTask_DCmotor2;

void setup(void)
{
    kxnTask_DCmotor1.setup(6, 9, 8); // A
    kxnTask_DCmotor2.setup(5, 7, 4); // B
    kxnTaskManager.add(this);
    setState(Demo1_fw1);
}

void loop(void)
{
    switch (getState())
    {
    case Demo1_fw1:
        kxnTask_DCmotor1.forward(90);
        kxnTask_DCmotor2.forward(90);
        kDelay(3000);
        setState(Demo1_stop1);
        break;

    case Demo1_stop1:
        kxnTask_DCmotor1.stop();
        kxnTask_DCmotor2.stop();
        kDelay(1000);
        setState(Demo1_tL);
        break;

    case Demo1_tL:
        kxnTask_DCmotor1.backward(90);
        kxnTask_DCmotor2.forward(90);
        kDelay(3000);
        setState(Demo1_stop2);
        break;

    case Demo1_stop2:
        kxnTask_DCmotor1.stop();
        kxnTask_DCmotor2.stop();
        kDelay(1000);
        setState(Demo1_fw2);

        break;

    case Demo1_fw2:
        kxnTask_DCmotor1.forward(90);
        kxnTask_DCmotor2.forward(90);
        kDelay(3000);
        setState(Demo1_stop3);

        break;

    case Demo1_stop3:
        kxnTask_DCmotor1.stop();
        kxnTask_DCmotor2.stop();
        kDelay(1000);
        setState(Demo1_tR);

        break;

    case Demo1_tR:
        kxnTask_DCmotor1.forward(90);
        kxnTask_DCmotor2.backward(90);
        kDelay(3000);
        setState(Demo1_stop4);

        break;

    case Demo1_stop4:
        kxnTask_DCmotor1.stop();
        kxnTask_DCmotor2.stop();
        kDelay(1000);
        setState(Demo1_bw);

        break;

    case Demo1_bw:
        kxnTask_DCmotor1.backward(90);
        kxnTask_DCmotor2.backward(90);
        kDelay(3000);
        setState(Demo1_stop5);

        break;

    case Demo1_stop5:
        kxnTask_DCmotor1.stop();
        kxnTask_DCmotor2.stop();
        kDelay(1000);
        break;

    default:
        break;
    }
}

END
#endif