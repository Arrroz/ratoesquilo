#ifndef CONTROL_H_
#define CONTROL_H_

#include <motors.hpp>
#include <line_sensors.hpp>
#include "wheel.hpp"

void motorControl(Motor *motorL, Motor *motorR, LineSensors *lineSensors, float dt);
void wheelControl(Wheel *wheelL, Wheel *wheelR, LineSensors *lineSensors, float dt);

#endif
