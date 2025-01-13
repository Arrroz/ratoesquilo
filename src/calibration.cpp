#include "calibration.hpp"

void calibrateLineSensors(LineSensors *lineSensors, Display *display) {
    static int stage = 0;

    if(display) display->print("Line Sensors\nCalibrating...\n(check serial)");

    // Reset calibration variables
    if(stage == 0) {
        Serial.println("Calibrating Line Sensors...");

        for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
            lineSensors->calibMins[i] = -1; // maximum possible value for an unsigned int
            lineSensors->calibMaxs[i] = 0;
        }
    }

    // Each stage update the minimum and maximum if they were found
    if(stage < 100) {
        lineSensors->read();

        for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
            if(lineSensors->values[i] < lineSensors->calibMins[i])
                lineSensors->calibMins[i] = lineSensors->values[i];
            if(lineSensors->values[i] > lineSensors->calibMaxs[i])
                lineSensors->calibMaxs[i] = lineSensors->values[i];
        }

        stage++;
    }

    // Print the results
    else {
        for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
            Serial.print(lineSensors->calibMins[i]);
            Serial.print("\t");
        }
        Serial.println();
        
        for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
            Serial.print(lineSensors->calibMaxs[i]);
            Serial.print("\t");
        }
        Serial.println();

        stage = 0;
    }
}

void calibrateLightSensor(Display *display) {
    float lux = getLux();

    if(lux == -1) {
        if(display) display->print("\nError");
        Serial.println("Error");
        return;
    }

    if(display) display->print("Light Sensor\n", lux);
    Serial.println(lux);
}

void calibrateEncoders(Encoder *encoderL, Encoder *encoderR, Display *display) {
    if(display) display->print("Encoders\n", encoderL->count, "     ", encoderR->count);
    Serial.print(encoderL->count);
    Serial.print("\t");
    Serial.print(encoderR->count);
}
