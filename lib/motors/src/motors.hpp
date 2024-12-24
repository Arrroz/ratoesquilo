#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <connections.hpp>

extern float lMotorInput, rMotorInput;

void setupMotors();
void brake();
void updateMotors();

#endif
