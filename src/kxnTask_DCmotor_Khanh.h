#ifndef kxnTask_DCmotor_h
#define kxnTask_DCmotor_h
#pragma once
#include "kxnTask.h"
#include "inttypes.h"
#include "Arduino.h"

void setup(int pwm_, int in1_, int in2_);
void forward(int iSpeed);
void backward(int iSpeed);
void start();
void stop();
void write_for(int8_t para_Dir_Spd, unsigned long _for);

DEFINE_TASK_STATE(kxnTask_DCmotor){
    kxnTask_DCmotor_DEPART_F,
    kxnTask_DCmotor_DEPART_B,
    kxnTask_DCmotor_FORWARD,
    kxnTask_DCmotor_BACKWARD,
    kxnTask_DCmotor_STOP,
};

CREATE_TASK(kxnTask_DCmotor)

uint8_t in1;
uint8_t in2;
uint8_t pwm;
uint8_t speed_forward;
uint8_t speed_backward;
unsigned long times_for;
uint8_t departSpeed;
unsigned long departTimes;

void setup(int pwm_, int in1_, int in2_)
{
    this->in1 = in1_;
    this->in2 = in2_;
    this->pwm = pwm_;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm, OUTPUT);
}

void setup(int pwm_, int in1_, int in2_, unsigned int _departSpeed, unsigned long _departTimes)
{
    this->in1 = in1_;
    this->in2 = in2_;
    this->pwm = pwm_;
    this->departSpeed = _departSpeed*255/100;
    this->departTimes = _departTimes;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm, OUTPUT);
}

void loop(void)
{
    switch (getState())
    {
    case kxnTask_DCmotor_DEPART_F:

        digitalWrite(this->in1, 1);
        digitalWrite(this->in2, 0);
        analogWrite(this->pwm, this->departSpeed);
        kDelay(this->departTimes);
        setState(kxnTask_DCmotor_FORWARD);
        break;


    case kxnTask_DCmotor_FORWARD:

        digitalWrite(this->in1, 1);
        digitalWrite(this->in2, 0);
        analogWrite(this->pwm, this->speed_forward);
        if (this->times_for != 0)
        {
            kDelay(this->times_for);
            setState(kxnTask_DCmotor_STOP);
        }
        break;

    case kxnTask_DCmotor_BACKWARD:
        if ((this->departSpeed != 0) && (this->departTimes >= 0))
        {
            digitalWrite(this->in1, 1);
            digitalWrite(this->in2, 0);
            analogWrite(this->pwm, this->departSpeed);
            kDelay(this->departTimes);
        }
        digitalWrite(this->in1, 0);
        digitalWrite(this->in2, 1);
        analogWrite(this->pwm, this->speed_backward);
        if (this->times_for != 0)
        {
            kDelay(this->times_for);
            setState(kxnTask_DCmotor_STOP);
        }
        break;

    case kxnTask_DCmotor_STOP:
        digitalWrite(this->in1, 0);
        digitalWrite(this->in2, 0);
        analogWrite(this->pwm, 0);
        break;

    default:
        break;
    }
}

void forward(int iSpeed)
{
    this->speed_forward = iSpeed * 255 / 100;
    this->start();
    if ((this->departSpeed != 0) && (this->departTimes > 0))
    {
        setState(kxnTask_DCmotor_DEPART_F);
    }
    else
    {
        setState(kxnTask_DCmotor_FORWARD);
    }
}

void backward(int iSpeed)
{
    this->speed_backward = iSpeed * 255 / 100;
    this->start();
    if ((this->departSpeed != 0) && (this->departTimes > 0))
    {
        setState(kxnTask_DCmotor_DEPART_B);
    }
    else
    {
        setState(kxnTask_DCmotor_BACKWARD);
    }
}

void start()
{
    kxnTaskManager.add(this);
}

void stop()
{
    setState(kxnTask_DCmotor_STOP);
    kDelay(0);
}

void write(int8_t para_Dir_Spd)
{
    if (para_Dir_Spd > 0)
    {
        if (para_Dir_Spd >= 100)
        {
            para_Dir_Spd = 100;
        }
        this->forward(para_Dir_Spd);
    }
    else if (para_Dir_Spd < 0)
    {
        if (para_Dir_Spd <= -100)
        {
            para_Dir_Spd = -100;
        }
        this->backward(map(para_Dir_Spd, -1, -100, 1, 100));
    }
    else if (para_Dir_Spd == 0)
        this->stop();
}

void write_for(int8_t para_Dir_Spd, unsigned long _for)
{
    this->times_for = _for;
    this->write(para_Dir_Spd);
}
END
#endif