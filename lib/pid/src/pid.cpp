#include "pid.hpp"

PID_t::PID_t() {
    kp = 0;
    ki = 0;
    kd = 0;
    kf = 0;

    error = 0;
    iError = 0;
    dError = 0;
    prevError = 0;
    output = 0;
}

PID_t::PID_t(float kp, float ki, float kd, float kf): kp(kp), ki(ki), kd(kd), kf(kf) {
    error = 0;
    iError = 0;
    dError = 0;
    prevError = 0;
    output = 0;
}

float PID_t::update(float ref, float value, float dt) {
    // save previous error
    prevError = error;

    // error
    error = ref - value;

    // error integral
    iError += error * dt;

    // error derivative
    dError = (error - prevError) / dt;

    // calculate output
    output = kp*error + ki*iError + kd*dError + kf*ref;

    // clip output
    if(output > 1)
        output = 1;
    if(output < -1)
        output = -1;

    // anti windup
    if((output == 1 && error < 0) || (output == -1 && error > 0))
        iError -= error * dt; // undo integration
    
    return output;
}
