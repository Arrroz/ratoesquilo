#ifndef LINE_SENSORS_H_
#define LINE_SENSORS_H_

#include <Arduino.h>
#include <connections.hpp>
#include <QTRSensors.h>

#define LINE_SENSOR_COUNT 13 // max 13

#define LS_THRESHOLD 200

extern QTRSensors lineSensors;
extern uint16_t lineSensorValues[LINE_SENSOR_COUNT];
extern float linePos;

void setupLineSensors();
void readLineSensors();
bool horizontalLine();
bool noLine();

#endif
