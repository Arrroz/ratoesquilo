#include "control.hpp"

void brake(Motor *motorL, Motor *motorR) {
    motorL->input = -1;
    motorR->input = -1;
    motorL->update();
    motorR->update();

    delay(400);

    motorL->input = 0;
    motorR->input = 0;
    motorL->update();
    motorR->update();
}

bool motorControl(Motor *motorL, Motor *motorR, LineSensors *lineSensors, PID_t *pid, float speed, float dt) {
    static float speedDiff;

    lineSensors->update();

    if(lineSensors->fullLine || lineSensors->noLine) {
        brake(motorL, motorR);
        return true;
    }

    speedDiff = pid->update(0, lineSensors->linePos, dt);

    motorL->input = speed;
    motorR->input = speed;
    if(speedDiff > 0)
        motorR->input -= speedDiff;
    else
        motorL->input += speedDiff;

    motorL->update();
    motorR->update();

    return false;
}

bool wheelControl(Wheel *wheelL, Wheel *wheelR, LineSensors *lineSensors, PID_t *pid, float speed, float dt) {
    static float speedDiff;

    lineSensors->update();

    if(lineSensors->fullLine || lineSensors->noLine) {
        brake(wheelL->motor, wheelR->motor);
        return true;
    }

    speedDiff = pid->update(0, lineSensors->linePos, dt);

    wheelL->refSpeed = speed;
    wheelR->refSpeed = speed;
    if(speedDiff > 0)
        wheelR->refSpeed -= speedDiff;
    else
        wheelL->refSpeed += speedDiff;

    wheelL->update(dt);
    wheelR->update(dt);

    return false;
}
