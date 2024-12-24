#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>

#define NUM_CALIBS 3

extern Display display;

void calibrateLineSensors();
void calibrateLightSensor();
void calibrateEncoders();
