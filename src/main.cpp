#include <Arduino.h>

#include <interface.hpp>
#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>
#include <motors.hpp>

#include "tests.hpp"
#include "calibration.hpp"

enum Mode_t {
    race, test, calib
};
Mode_t mode;

#define TIME_INTERVAL 0.003 // in seconds
unsigned long currTime, prevTime;

// TODO: add dipswitch and use it to determine which test/calibration routine runs
// TODO: change libraries to work with objects instead of poluting the main namespace with variables specific to this robot
// TODO: make constructors take the appropriate pins for initialization without including connections.hpp
// TODO: create robot class with robot state variables (position, orientation, velocities, velocities' references...)
// TODO: create control file with functions for coordinated movement (PID on wheels, PID on robot state...)
// TODO: test line sensors with a different number of sensors
// TODO: test light sensor (currently not working) and it's calibration routine

#define BASE_SPEED 0.4
#define KP 5
#define KD 1

void control() {
    static float prevLinePos = 0;
    static float speedDiff;

    prevLinePos = linePos;

    readLineSensors();

    if(horizontalLine() || noLine()) {
        brake();
        displayPrint("Stop");
        while(true);
    }

    speedDiff = KP*linePos + KD*(linePos-prevLinePos)/TIME_INTERVAL;

    lMotorInput = BASE_SPEED - speedDiff;
    rMotorInput = BASE_SPEED + speedDiff;

    updateMotors();
}

void setup() {
    // Hardware setup
    setupDisplay();

    displayPrint("Setting up");

    Serial.begin(9600);
    while(!Serial);

    setupInterface();
    setupLightSensor();
    setupLineSensors();
    setupEncoders();
    setupMotors();
    
    delay(500);

    // Program initialization
    readDipswitch();
    if(!dipswitch[0])
        mode = race;
    else if(!dipswitch[1])
        mode = test;
    else
        mode = calib;

    currTime = millis();
    prevTime = currTime;

    displayPrint("Ready");
}

void loop() {
    while(currTime - prevTime < TIME_INTERVAL*1000)
        currTime = millis();
    prevTime = currTime;

    switch(mode) {
        case race:
            // static unsigned long t0, t1;
            // t0 = micros();
            control();
            // t1 = micros();
            // Serial.println(t1-t0);
            
            break;
        
        case test:
            testDisplay(currTime);
            // testLightSensor();
            // testLineSensors();
            // testEncoders();
            // testMotors(currTime);

            break;
        
        case calib:
            // calibrateLineSensors();
            // calibrateLightSensor();
            calibrateEncoders();

            break;
        
        default:
            displayPrint("Unknown mode");

            break;
    }
}
