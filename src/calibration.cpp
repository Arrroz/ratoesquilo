#include "calibration.hpp"

void calibrateLineSensors(LineSensors *lineSensors, Display *display) {
    static int stage = 0;

    static uint16_t mins[LINE_SENSOR_COUNT], maxs[LINE_SENSOR_COUNT];

    if(display) display->printAll("Calib LS");

    // Reset calibration variables
    if(stage == 0) {
        Serial.println("Calibrating Line Sensors...");

        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            mins[i] = -1; // maximum possible value for an unsigned int
            maxs[i] = 0;
        }
    }

    // Each stage update the minimum and maximum if they were found
    if(stage < 400) {
        lineSensors->read();

        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            if(lineSensors->values[i] < mins[i])
                mins[i] = lineSensors->values[i];
            if(lineSensors->values[i] > maxs[i])
                maxs[i] = lineSensors->values[i];
        }

        stage++;
    }

    // Print the results
    if(stage >= 400) {
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(mins[i]);
            Serial.print("\t");
        }
        Serial.println();
        
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(maxs[i]);
            Serial.print("\t");
        }
        Serial.println();

        stage = 0;
    }
}

void calibrateLightSensor(Display *display) {
    float lux = getLux();

    if(lux == -1) {
        if(display) display->printAll("Error");
        Serial.println("Error");
        return;
    }

    if(display) display->printAll(lux);
    Serial.println(lux);
}

void calibrateEncoders(Encoder *encoderL, Encoder *encoderR, Display *display) {
    if(display) display->printAll(encoderL->count, "  ", encoderR->count);
    Serial.print(encoderL->count);
    Serial.print("\t");
    Serial.print(encoderR->count);
}
