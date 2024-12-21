#include <Arduino.h>

#include <display.hpp>
#include <encoders.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <motors.hpp>
#include <encoders.hpp>

#define TESTING
// #define CALIBRATING

#ifdef TESTING
#include "tests.hpp"
#endif
#ifdef CALIBRATING
#include "calibration.hpp"
#endif

#define TIME_INTERVAL 0.003 // in seconds
unsigned long currTime, prevTime;

// TODO: add dipswitch and use it to determine which test/calibration routine runs
// TODO: test motor lib changes
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
    // moveLR(leftSpeed, rightSpeed);
}

void setup() {
    setupDisplay();

    displayPrint("Setting up");

    Serial.begin(9600);
    while(!Serial);

    setupLightSensor();
    setupLineSensors();
    setupEncoders();
    setupMotors();
    
    delay(500);

    currTime = millis();
    prevTime = currTime;

    displayPrint("Ready");
}

void loop() {
    while(currTime - prevTime < TIME_INTERVAL*1000)
        currTime = millis();
    prevTime = currTime;

    #if defined(TESTING)

        // testDisplay(currTime);
        // testLightSensor();
        // testLineSensors();
        // testEncoders();
        // testMotors(currTime);

    #elif defined(CALIBRATING)

        // calibrateLineSensors();
        // calibrateLightSensor();
        // calibrateEncoders();

    #else

    // static unsigned long t0, t1;
    // t0 = micros();
        control();
    // t1 = micros();
    // Serial.println(t1-t0);

    #endif
}
