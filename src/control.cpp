#include "control.hpp"

#define BASE_SPEED 0.4
#define KP 5
#define KD 1

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

void motorControl(Motor *motorL, Motor *motorR, LineSensors *lineSensors, float dt) {
    static float prevLinePos = 0;
    static float speedDiff;

    prevLinePos = lineSensors->linePos;

    lineSensors->update();

    if(lineSensors->fullLine || lineSensors->noLine) {
        brake(motorL, motorR);
        while(true);
    }

    speedDiff = KP*lineSensors->linePos + KD*(lineSensors->linePos-prevLinePos)/dt;

    motorL->input = BASE_SPEED - speedDiff;
    motorR->input = BASE_SPEED + speedDiff;

    motorL->update();
    motorR->update();
}

void wheelControl(Wheel *wheelL, Wheel *wheelR, LineSensors *lineSensors, float dt) {
    static float prevLinePos = 0;
    static float speedDiff;

    prevLinePos = lineSensors->linePos;

    lineSensors->update();

    if(lineSensors->fullLine || lineSensors->noLine) {
        brake(wheelL->motor, wheelR->motor);
        while(true);
    }

    speedDiff = KP*lineSensors->linePos + KD*(lineSensors->linePos-prevLinePos)/dt;

    wheelL->refSpeed = BASE_SPEED - speedDiff;
    wheelR->refSpeed = BASE_SPEED + speedDiff;

    wheelL->update(dt);
    wheelR->update(dt);
}
