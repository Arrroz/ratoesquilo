#ifndef TESTS_H_
#define TESTS_H_

#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>
#include <motors.hpp>

#define NUM_TESTS 5

void testDisplay(Display *display);
void testLightSensor(LightSensor *lightSensor, Display *display = NULL);
void testLineSensors(LineSensors *lineSensors, Display *display = NULL);
void testEncoders(Encoder *encoderL, Encoder *encoderR, Display *display = NULL);
void testMotors(Motor *motorL, Motor *motorR, Display *display = NULL);

#endif
