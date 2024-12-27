#include "line_sensors.hpp"

#define LS_CALIB_MIN 33
#define LS_CALIB_MAX 800

#define LS_PITCH 0.004 // in meters

#define LS_THRESHOLD 200
#define LS_NOISE_THRESHOLD 50

#define LS_FULL_LINE_DETECTIONS_REQ 8

LineSensors::LineSensors(const uint8_t sensorPins[LINE_SENSOR_COUNT],
                        uint8_t oddEmitterPin,
                        uint8_t evenEmitterPin) {
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++)
        this->sensorPins[i] = sensorPins[i];
    this->oddEmitterPin = oddEmitterPin;
    this->evenEmitterPin = evenEmitterPin;
    
    digitalWrite(oddEmitterPin, HIGH);
    digitalWrite(evenEmitterPin, HIGH);
    
    enabled = true;
}

void LineSensors::read() {
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++)
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
    for (uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
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
    linePos -= (LINE_SENSOR_COUNT-1)/2.0; // center
    linePos *= LS_PITCH; // scale to meters
}
