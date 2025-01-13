#ifndef LINE_SENSORS_H_
#define LINE_SENSORS_H_

#include <Arduino.h>

class LineSensors {
public:
    LineSensors(uint8_t sensorCount, const uint8_t sensorPins[], uint8_t oddEmitterPin, uint8_t evenEmitterPin);
    ~LineSensors();
    void read();
    void update();

    uint8_t sensorCount;
    uint16_t *values;
    float linePos = 0;
    bool fullLine = false;
    bool noLine = false;

    uint16_t *calibMins, *calibMaxs;

    bool enabled;

private:
    uint8_t *sensorPins;
    uint8_t oddEmitterPin;
    uint8_t evenEmitterPin;
};

#endif
