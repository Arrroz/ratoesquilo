#include "line_sensors.hpp"

#define LS_CALIB_MIN 20
#define LS_CALIB_MAX 700

#define LS_PITCH 0.004 // in meters

#define LS_THRESHOLD 200
#define LS_NOISE_THRESHOLD 50

#define LS_FULL_LINE_DETECTIONS_REQ 8

LineSensors::LineSensors(uint8_t sensorCount, const uint8_t sensorPins[], uint8_t oddEmitterPin, uint8_t evenEmitterPin) : sensorCount(sensorCount), oddEmitterPin(oddEmitterPin), evenEmitterPin(evenEmitterPin) {
    this->sensorPins = (uint8_t*)malloc(sensorCount * sizeof(uint8_t));
    values = (uint16_t*)malloc(sensorCount * sizeof(uint16_t));
    calibMins = (uint16_t*)malloc(sensorCount * sizeof(uint16_t));
    calibMaxs = (uint16_t*)malloc(sensorCount * sizeof(uint16_t));
    
    for(uint8_t i = 0; i < sensorCount; i++)
        this->sensorPins[i] = sensorPins[i];
    
    digitalWrite(oddEmitterPin, HIGH);
    digitalWrite(evenEmitterPin, HIGH);
    
    enabled = true;
}

LineSensors::~LineSensors() {
    free(sensorPins);
    free(values);
    free(calibMins);
    free(calibMaxs);
}

void LineSensors::read() {
    for(uint8_t i = 0; i < sensorCount; i++)
        values[i] = analogRead(sensorPins[i]);
}

void LineSensors::update() {
    if(!enabled)
        return;
    
    // Get readings
    read();

    uint32_t avg = 0;
    uint16_t sum = 0;
    uint8_t detectionCount = 0;
    for (uint8_t i = 0; i < sensorCount; i++) {
        // Normalize each sensor reading
        values[i] = (((int32_t)values[i]) - LS_CALIB_MIN) * 1000 / (LS_CALIB_MAX-LS_CALIB_MIN);
        if (values[i] < 0)
            values[i] = 0;
        else if (values[i] > 1000)
            values[i] = 1000;

        // Clean out noisy measurements
        if (values[i] < LS_NOISE_THRESHOLD)
            continue;

        // Find how many sensors detected the line
        if (values[i] > LS_THRESHOLD)
            detectionCount++;

        // Calculate contribution to line position
        avg += (uint32_t)values[i] * (i * 1000);
        sum += values[i];
    }

    // Update relevant variables
    fullLine = (detectionCount >= LS_FULL_LINE_DETECTIONS_REQ);
    noLine = (detectionCount == 0);

    // Get line position
    if(sum == 0) {
        linePos = 0;
        return;
    }
    linePos = avg / sum / 1000;
    linePos -= (sensorCount-1)/2.0; // center
    linePos *= LS_PITCH; // scale to meters
}
