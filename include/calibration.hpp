#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>

#define NUM_CALIBS 3

void calibrateLineSensors(LineSensors *lineSensors, Display *display = NULL);
void calibrateLightSensor(LightSensor *lightSensor, Display *display = NULL);
void calibrateEncoders(Encoder *encoderL, Encoder *encoderR, Display *display = NULL);

#endif
