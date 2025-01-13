#ifndef WHEEL_H_
#define WHEEL_H_

#include <Arduino.h>

#include <motors.hpp>
#include <encoders.hpp>
#include <pid.hpp>

#define WHEEL_KP 1
#define WHEEL_KI 0
#define WHEEL_KD 0
#define WHEEL_KF 0.01

class Wheel {
public:
    Wheel(Motor *motor, Encoder *enc);
    void update(float dt);

    Motor *motor;
    Encoder *enc;
    PID_t controller;
    float refSpeed;

    bool enabled;
};

#endif
