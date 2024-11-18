#include "line_sensors.hpp"

#define LS_PITCH 0.004 // in meters

// #define LS_CALIB_MIN 76
// #define LS_CALIB_MAX 380
#define LS_CALIB_MIN 33
#define LS_CALIB_MAX 800

#define LS_NOISE_THRESHOLD 50

#define LS_HORIZONTAL_LINE_DETECTIONS_REQ 7

bool usingLineSensors = true;

QTRSensors lineSensors;
uint16_t lineSensorValues[LINE_SENSOR_COUNT];
float linePos;
uint8_t lineSensorDetections;

void setupLineSensors() {   
    lineSensors.setTypeAnalog();

    // Find which sensors to use based on the chosen LINE_SENSOR_COUNT and set them up
    uint8_t lineSensorsTotal = sizeof(PINOUT_LS_SENSORS) / sizeof(PINOUT_LS_SENSORS[0]);
    uint8_t lineSensorsPinout[LINE_SENSOR_COUNT] = {};
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        uint8_t j = i + (lineSensorsTotal - LINE_SENSOR_COUNT) / 2;
        lineSensorsPinout[i] = PINOUT_LS_SENSORS[j];
    }
    lineSensors.setSensorPins(lineSensorsPinout, LINE_SENSOR_COUNT);

    lineSensors.setEmitterPins(PINOUT_LS_EMMITER_ODD, PINOUT_LS_EMMITER_EVEN);
    lineSensors.emittersOn();

    lineSensors.setSamplesPerSensor(1);

    delay(500);
}

void normalizeLineSensorValues() {
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        int16_t value = 0;

        value = (((int32_t)lineSensorValues[i]) - LS_CALIB_MIN) * 1000 / (LS_CALIB_MAX-LS_CALIB_MIN);

        if (value < 0)
            value = 0;
        else if (value > 1000)
            value = 1000;

        lineSensorValues[i] = value;
    }
}

void updateLinePos() {
    uint32_t avg = 0;
    uint16_t sum = 0;
    lineSensorDetections = 0;

    for (uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        uint16_t value = lineSensorValues[i];

        if (value > LS_THRESHOLD)
            lineSensorDetections++;

        // only consider values above a noise threshold
        if (value < LS_NOISE_THRESHOLD)
            continue;

        avg += (uint32_t)value * (i * 1000);
        sum += value;
    }

    if(sum == 0) {
        linePos = 0;
        return;
    }

    linePos = avg / sum / 1000;
    linePos -= (LINE_SENSOR_COUNT-1)/2.0; // center
    linePos *= LS_PITCH; // scale to meters
}

void readLineSensors() {
    if(!usingLineSensors)
        return;
    
    lineSensors.read(lineSensorValues, QTRReadMode::Manual);

    normalizeLineSensorValues();

    updateLinePos();
}

bool horizontalLine() {
    return (lineSensorDetections > LS_HORIZONTAL_LINE_DETECTIONS_REQ);
}

bool noLine() {
    return (lineSensorDetections == 0);
}
