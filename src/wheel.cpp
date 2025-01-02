#include "wheel.hpp"

Wheel::Wheel(Motor *motor, Encoder *enc) {
    this->motor = motor;
    this->enc = enc;
    controller = PID_t(WHEEL_KP, WHEEL_KI, WHEEL_KD, WHEEL_KF);

    enabled = true;
}

void Wheel::update(float dt) {
    if(!enabled)
        return;

    enc->updateSpeed(dt);
    motor->input = controller.update(refSpeed, enc->speed, dt);
    motor->update();
}
