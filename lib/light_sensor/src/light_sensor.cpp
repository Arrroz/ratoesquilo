#include "light_sensor.hpp"

#define ILLUMINATED_LUX_DIFF 100

#define BASELINE_READINGS_COUNT 50

LightSensor::LightSensor() {
    enabled = false;
}

void LightSensor::setup() {
    if(!begin())
        return;

    // get readings quicker to improve sampling rate
    setIntegrationTime(VEML7700_IT_25MS);

    enabled = true;

    // get some initial readings to establish the baseline
    baselineLux = 0;
    for(uint16_t i = 0; i < BASELINE_READINGS_COUNT; i++) {
        baselineLux += readLux() / BASELINE_READINGS_COUNT;
        delay(1);
    }
}

float LightSensor::readLux() {
    if(!enabled)
        return -1;

    return Adafruit_VEML7700::readLux();
}

int8_t LightSensor::illuminated() {
    if(!enabled)
        return -1;

    if(readLux() - baselineLux > ILLUMINATED_LUX_DIFF)
        return 1;
    return 0;
}
