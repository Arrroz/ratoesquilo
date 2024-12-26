#include <Arduino.h>

// #include <interface.hpp>
#include <switch.hpp>
#include <dipswitch.hpp>
#include <button.hpp>
#include <display.hpp>
#include <light_sensor.hpp>
#include <line_sensors.hpp>
#include <encoders.hpp>
#include <motors.hpp>

#include "tests.hpp"
#include "calibration.hpp"

Switch debugSw(PINOUT_DEBUG_SW);
Dipswitch dipswitch(PINOUT_DIPSWITCH);
Button btn1(PINOUT_BTN1, true), btn2(PINOUT_BTN2, true);

Display display;

Encoder encoderL(PINOUT_ENC_LA, PINOUT_ENC_LB);
Encoder encoderR(PINOUT_ENC_RA, PINOUT_ENC_RB);

enum Mode_t {
    race, test, calib
};
Mode_t mode;

int testNum = 0, calibNum = 0;

#define TIME_INTERVAL 0.003 // in seconds
unsigned long currTime, prevTime;

// TODO: change libraries to work with objects instead of poluting the main namespace with variables specific to this robot
// TODO: make constructors take the appropriate pins for initialization without including connections.hpp
// TODO: create robot class with robot state variables (position, orientation, velocities, velocities' references...)
// TODO: create control file with functions for coordinated movement (PID on wheels, PID on robot state...)
// TODO: test line sensors with a different number of sensors
// TODO: test light sensor (currently not working) and it's calibration routine
// TODO: check display scrolling functions
// TODO: config files for spread out constants?

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
        display.printAll("Stop");
        while(true);
    }

    speedDiff = KP*linePos + KD*(linePos-prevLinePos)/TIME_INTERVAL;

    lMotorInput = BASE_SPEED - speedDiff;
    rMotorInput = BASE_SPEED + speedDiff;

    updateMotors();
}

void setup() {
    // Hardware setup
    display.setup();

    display.printAll("Setting up");

    Serial.begin(9600);
    while(!Serial);

    // setupInterface();
    setupLightSensor();
    setupLineSensors();
    setupMotors();
    
    delay(500);

    // Program initialization
    if(!dipswitch[0])
        mode = race;
    else if(!dipswitch[1])
        mode = test;
    else
        mode = calib;

    currTime = millis();
    prevTime = currTime;

    display.printAll("Ready");
}

void loop() {
    while(currTime - prevTime < TIME_INTERVAL*1000)
        currTime = millis();
    prevTime = currTime;

    switch(mode) {
    case race:
        // static unsigned long t0, t1;
        // t0 = micros();
        // control();
        // t1 = micros();
        // Serial.println(t1-t0);
        display.printAll(debugSw.read());
        
        break;
    
    case test:
        // Cycle between tests with button presses
        if(btn1.read()) testNum++;
        if(btn2.read()) testNum--;

        switch (testNum) {
        case 0:
            testDisplay(currTime);
            break;
        
        case 1:
            testLightSensor();
            break;
        
        case 2:
            testLineSensors();
            break;
        
        case 3:
            testEncoders();
            break;

        case 4:
            testMotors(currTime);
            break;
        
        default:
            // if the testNum is out of bounds, get it back in
            testNum = (testNum + NUM_TESTS) % NUM_TESTS;
            break;
        }

        // Disable motors if their test is not running
        if(testNum != 4) {
            lMotorInput = 0;
            rMotorInput = 0;
            updateMotors();
        }

        break;
    
    case calib:
        // Cycle between calibration routines with button presses
        if(btn1.read()) calibNum++;
        if(btn2.read()) calibNum--;

        switch(calibNum) {
        case 0:
            calibrateLineSensors();
            break;
        
        case 1:
            calibrateLightSensor();
            break;
        
        case 2:
            calibrateEncoders();
            break;
        
        default:
            // if the calibNum is out of bounds, get it back in
            calibNum = (calibNum + NUM_CALIBS) % NUM_CALIBS;
            break;
        }

        break;
    
    default:
        display.printAll("Unknown mode");
        break;
    }
}
