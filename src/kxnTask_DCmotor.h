#ifndef kxnTask_DCmotor_h
#define kxnTask_DCmotor_h
#pragma once
#include "kxnTask.h"
// #include "inttypes.h"

void setup(int pwm_, int in1_, int in2_);
void forward(int iSpeed);
// void backward(int iSpeed);
void start();
void stop();
// void setTimeRun(unsigned long ul_timerun_);
// void checkStop();

DEFINE_TASK_STATE(kxnTask_DCmotor){
    kxnTask_DCmotor_FORWARD,
    kxnTask_DCmotor_BACKWARD,
    kxnTask_DCmotor_STOP,
};

CREATE_TASK(kxnTask_DCmotor)

uint8_t in1;
uint8_t in2;
uint8_t pwm;
uint8_t speed;

void setup(int pwm_, int in1_, int in2_)
{
    this->in1 = in1_;
    this->in2 = in2_;
    this->pwm = pwm_;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm, OUTPUT);
}

void loop(void)
{
    switch (getState())
    {
    case kxnTask_DCmotor_FORWARD:
        digitalWrite(this->in1, 1);
        digitalWrite(this->in2, 0);
        analogWrite(this->pwm, this->speed);
        break;

    default:
        break;
    }
}

void forward(int iSpeed)
{
    this->speed = iSpeed*255/100;
    this->start();
    setState(kxnTask_DCmotor_FORWARD);
}

void start()
{
    kxnTaskManager.add(this);
}

void stop()
{
    // this->LED_mode = kxnTaskLED_MODE_STOP;
    kDelay(0);
    setStateIdle();
}

// void backward(int iSpeed){
//     digitalWrite(this->in1, 0);
//     digitalWrite(this->in2, 1);
//     analogWrite(this->pwm, iSpeed);
//     this->resetTimeRun();
// }

// void stop(){
//     digitalWrite(this->in1, 0);
//     digitalWrite(this->in2, 0);
//     analogWrite(this->pwm, 0);
// }

END
#endif