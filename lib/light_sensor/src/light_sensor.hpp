#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_

#include <Adafruit_VEML7700.h>

class LightSensor : public Adafruit_VEML7700 {
public:
    LightSensor();
    void setup();
    float readLux();
    int8_t illuminated();

    float baselineLux;

    bool enabled;
};


#endif
