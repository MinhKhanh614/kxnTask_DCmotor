#pragma once
#define POSITIVE 1
#define NEGATIVE 0
#include "kxnTask.h"

DEFINE_TASK_STATE(kxnTask_DCmotor){
    kxnTask_DCmotor_RUN,
    kxnTask_DCmotor_DEPART,
    kxnTask_DCmotor_IDLE,
};

CREATE_TASK(kxnTask_DCmotor)

byte pin1, pin2, pinPWM, speed, speedDepart;
bool direct;
unsigned long timeRun, timeRunDepart = 100;

void setup(byte pin1, byte pin2, byte pinPWM, byte speedDepart)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pinPWM = pinPWM;
    this->speedDepart = speedDepart;

    pinMode(this->pin1, OUTPUT);
    pinMode(this->pin2, OUTPUT);
    pinMode(this->pinPWM, OUTPUT);

    if (this->speedDepart > 100)
        this->speedDepart = 100;
    else if (this->speedDepart < 0)
        this->speedDepart = 0;
    stop();
}

void loop()
{
    switch (getState())
    {
    case kxnTask_DCmotor_RUN:
        this->run(this->speed);
        if (this->timeRun >= 0)
        {
            kDelay(this->timeRun);
            setState(kxnTask_DCmotor_IDLE);
        }
        break;

    case kxnTask_DCmotor_DEPART:
        this->run(this->speedDepart);
        kDelay(this->timeRunDepart);
        setState(kxnTask_DCmotor_RUN);
        break;

    case kxnTask_DCmotor_IDLE:
        this->stop();
        break;

    default:
        break;
    }
}

void start()
{
    kxnTaskManager.add(this);
    if (this->speed >= this->speedDepart)
        setState(kxnTask_DCmotor_RUN);
    else
        setState(kxnTask_DCmotor_DEPART);
}

void stop()
{
    digitalWrite(this->pin1, 0);
    digitalWrite(this->pin2, 0);
    analogWrite(this->pinPWM, 0);
    kDelay(0);
    this->resetAllPa();
    setStateIdle();
}



void run(uint8_t speed)
{
    digitalWrite(this->pin1, this->direct);
    digitalWrite(this->pin2, !this->direct);
    analogWrite(this->pinPWM, speed * 255 / 100);
}

void resetAllPa()
{
    this->speed = 0;
    this->timeRun = 0;
}

void write(int8_t speed, unsigned long time)
{
    this->timeRun = time;
    if ((speed > 0) && (speed <= 100) || (speed < 0) && (speed >= -100))
    {
        if (speed > 0)
        {
            this->speed = speed;
            this->direct = POSITIVE;
        }
        else if (speed < 0)
        {
            this->speed = -speed;
            this->direct = NEGATIVE;
        }
        this->start();
    }
    else
    {
        this->stop();
    }
}

void write(int8_t speed)
{
    this->write(speed,-1);
}

END