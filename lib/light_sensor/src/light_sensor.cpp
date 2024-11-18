#include "light_sensor.hpp"

#define ILLUMINATED_LUX_DIFF 100

bool usingLightSensor = true;

Adafruit_VEML7700 lightSensor;
float baselineLux;

void setupLightSensor() {
    if(!lightSensor.begin()) {
        usingLightSensor = false;
        return;
    }

    // get readings quicker to improve sampling rate
    lightSensor.setIntegrationTime(VEML7700_IT_25MS);

    baselineLux = 0;
    uint8_t i;
    for(i = 0; i < 50; i++) {
      baselineLux += lightSensor.readLux();
      delay(1);
    }
    baselineLux /= i;
}

float getLux() {
    if(!usingLightSensor)
        return -1;
    
    return lightSensor.readLux();
}

uint8_t illuminated() {
    if(!usingLightSensor)
        return -1;

    if(getLux() - baselineLux > ILLUMINATED_LUX_DIFF)
        return 1;
    return 0;
}
