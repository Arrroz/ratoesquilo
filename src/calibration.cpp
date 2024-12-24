#include "calibration.hpp"

void calibrateLineSensors() {
    static int stage = 0;

    display.printAll("Calib LS");

    if(stage == 0) {
        Serial.println("Calibrating Line Sensors...");
        lineSensors.resetCalibration();
    }

    if(stage < 400) {
        lineSensors.calibrate();
        stage++;
    }

    if(stage >= 400) {
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(lineSensors.calibrationOn.minimum[i]);
            Serial.print("\t");
        }
        Serial.println();
        for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
            Serial.print(lineSensors.calibrationOn.maximum[i]);
            Serial.print("\t");
        }
        Serial.println();

        stage = 0;
    }
}

void calibrateLightSensor() {
    float lux = getLux();

    if(lux == -1) {
        display.printAll("Error");
        Serial.println("Error");
        return;
    }

    display.printAll(lux);
    Serial.println(lux);
}

void calibrateEncoders() {
    // static int16_t countL = 0;
    // static int16_t countR = 0;

    // updateEncoderSpeeds();

    // countL += speedL * ENC_PULSES_PER_METER;
    // countR += speedR * ENC_PULSES_PER_METER;

    display.printAll(encoderL.count, "  ", encoderR.count);
}
