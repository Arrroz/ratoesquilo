#ifndef CONTROL_H_
#define CONTROL_H_

#include <motors.hpp>
#include <line_sensors.hpp>
#include "wheel.hpp"
#include "pid.hpp"

bool motorControl(Motor *motorL, Motor *motorR, LineSensors *lineSensors, PID_t *pid, float speed, float dt);
bool wheelControl(Wheel *wheelL, Wheel *wheelR, LineSensors *lineSensors, PID_t *pid, float speed, float dt);

#endif
