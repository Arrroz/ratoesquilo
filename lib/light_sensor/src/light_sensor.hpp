#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_

#include <Adafruit_VEML7700.h>

void setupLightSensor();
float getLux();
uint8_t illuminated();

#endif
