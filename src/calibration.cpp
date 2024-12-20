#include "calibration.hpp"

void calibrateLineSensors() {
    Serial.println("Calibrating Line Sensors...");

    lineSensors.resetCalibration();
    for(uint16_t i = 0; i < 400; i++)
        lineSensors.calibrate();

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
    
    delay(200);
}

void calibrateLightSensor() {
    float lux = getLux();

    displayPrint(lux);
    Serial.println(lux);
}

void calibrateEncoders() {
    static int16_t countL = 0;
    static int16_t countR = 0;

    updateEncoderSpeeds();

    countL += speedL * ENC_PULSES_PER_METER;
    countR += speedR * ENC_PULSES_PER_METER;

    displayPrint(countL, "  ", countR);
}
