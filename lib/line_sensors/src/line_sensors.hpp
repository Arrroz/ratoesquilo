#ifndef LINE_SENSORS_H_
#define LINE_SENSORS_H_

#include <Arduino.h>

// TODO: find a way to not have to access this outside of the lib
#define LINE_SENSOR_COUNT 13 // max 13

class LineSensors {
public:
    LineSensors();
    void setup(const uint8_t sensorPins[LINE_SENSOR_COUNT], uint8_t oddEmitterPin, uint8_t evenEmitterPin);
    void read();
    void update();

    uint16_t values[LINE_SENSOR_COUNT];
    float linePos;
    bool fullLine;
    bool noLine;

    bool enabled;

private:
    uint8_t sensorPins[LINE_SENSOR_COUNT];
    uint8_t oddEmitterPin;
    uint8_t evenEmitterPin;
};

#endif
