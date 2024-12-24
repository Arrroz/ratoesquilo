#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>
#include <motors.hpp>

#define NUM_TESTS 5

extern Display display;
extern Encoder encoderL, encoderR;

void testDisplay(unsigned long time);
void testLightSensor();
void testLineSensors();
void testEncoders();
void testMotors(unsigned long time);
