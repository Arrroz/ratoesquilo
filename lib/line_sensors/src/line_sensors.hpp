#ifndef LINE_SENSORS_H_
#define LINE_SENSORS_H_

#include <Arduino.h>
#include <QTRSensors.h>

#define LINE_SENSOR_COUNT 13 // max 13

class LineSensors : public QTRSensors {
public:
    LineSensors();
    void setup(const uint8_t sensorPins[LINE_SENSOR_COUNT], uint8_t oddEmmiterPin, uint8_t evenEmmiterPin);
    void update();

    uint16_t values[LINE_SENSOR_COUNT];
    float linePos;
    bool horizontalLine;
    bool noLine;

    bool enabled;
};

#endif
