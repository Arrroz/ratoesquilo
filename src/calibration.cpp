#include "calibration.hpp"

void calibrateLineSensors(LineSensors *lineSensors, Display *display) {
    static int stage = 0;

    if(display) display->printAll("Calib LS");

    if(stage == 0) {
        Serial.println("Calibrating Line Sensors...");
        lineSensors->resetCalibration();
    }

    if(stage < 400) {
        lineSensors->calibrate();
        stage++;
    }

    if(stage >= 400) {
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(lineSensors->calibrationOn.minimum[i]);
            Serial.print("\t");
        }
        Serial.println();
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(lineSensors->calibrationOn.maximum[i]);
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
