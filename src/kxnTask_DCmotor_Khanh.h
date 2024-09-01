// Tiền xử lý
#ifndef kxnTask_DCmotor_h
#define kxnTask_DCmotor_h
#pragma once
#include "kxnTask.h"
#include "Arduino.h"

// Định nghĩa & khởi tạo biến
DEFINE_TASK_STATE(kxnTask_DCmotor){
    // kxnTask_DCmotor_IDLE,
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
uint8_t motorState;
uint8_t motorLastState;

// Hàm thực thi
void setup(int pwm_, int in1_, int in2_)
{
    this->in1 = in1_;
    this->in2 = in2_;
    this->pwm = pwm_;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm, OUTPUT);

    setState(kxnTask_DCmotor_IDLE);
}

void setup(int pwm_, int in1_, int in2_, unsigned int _departSpeed, unsigned long _departTimes)
{
    this->in1 = in1_;
    this->in2 = in2_;
    this->pwm = pwm_;
    this->departSpeed = _departSpeed * 255 / 100;
    this->departTimes = _departTimes;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm, OUTPUT);
}

void loop(void)
{
    switch (getState())
    {
    case kxnTask_DCmotor_IDLE:
        stopMotor();
        kDelay(0);

        break;

    case kxnTask_DCmotor_DEPART_F:
        departPositive();
        kDelay(this->departTimes);
        setState(kxnTask_DCmotor_FORWARD);
        break;

    case kxnTask_DCmotor_DEPART_B:
        departNegative();
        break;

    case kxnTask_DCmotor_FORWARD:
        runMotorPositive();
        time_for();
        break;

    case kxnTask_DCmotor_BACKWARD:
        runMotorNegative();
        time_for();
        break;

    case kxnTask_DCmotor_STOP:
        stopMotor();
        break;

    default:
        break;
    }
}

void forward(int iSpeed)
{
    this->speed_forward = iSpeed * 255 / 100;
    this->start();
    if ((this->departSpeed > 0) && (this->departTimes > 0))
    {
        if (this->speed_forward < this->departSpeed)
        {
            setState(kxnTask_DCmotor_DEPART_F);
        }
        else
        {
            setState(kxnTask_DCmotor_FORWARD);
        }
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
    if ((this->departSpeed > 0) && (this->departTimes > 0))
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

void departPositive()
{
    this->motorLastState = kxnTask_DCmotor_DEPART_F;
    digitalWrite(this->in1, 1);
    digitalWrite(this->in2, 0);
    analogWrite(this->pwm, this->departSpeed);
}

void departNegative()
{
    this->motorLastState = kxnTask_DCmotor_DEPART_B;
    digitalWrite(this->in1, 0);
    digitalWrite(this->in2, 1);
    analogWrite(this->pwm, this->departSpeed);
    kDelay(this->departTimes);
    setState(kxnTask_DCmotor_BACKWARD);
}

void stopMotor()
{
    digitalWrite(this->in1, 0);
    digitalWrite(this->in2, 0);
    analogWrite(this->pwm, 0);
    kDelay(0);
}

void runMotorPositive()
{
    this->motorLastState = kxnTask_DCmotor_FORWARD;
    digitalWrite(this->in1, 1);
    digitalWrite(this->in2, 0);
    analogWrite(this->pwm, this->speed_forward);
}

void runMotorNegative()
{
    this->motorLastState = kxnTask_DCmotor_BACKWARD;
    digitalWrite(this->in1, 0);
    digitalWrite(this->in2, 1);
    analogWrite(this->pwm, this->speed_forward);
}

void time_for()
{
    kDelay(this->times_for);
    setState(kxnTask_DCmotor_STOP);
}

uint8_t checkState()
{
    return motorLastState;
}

void init()
{
    if (this->motorLastState != kxnTask_DCmotor_IDLE)
    {
        this->motorLastState = kxnTask_DCmotor_IDLE;
        setState(kxnTask_DCmotor_IDLE);
    }
}
END
#endif