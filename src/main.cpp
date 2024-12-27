#include <Arduino.h>

#include <connections.hpp>

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

LineSensors lineSensors(PINOUT_LS_SENSORS, PINOUT_LS_EMITTER_ODD, PINOUT_LS_EMITTER_EVEN);
Encoder encoderL(PINOUT_ENC_LA, PINOUT_ENC_LB);
Encoder encoderR(PINOUT_ENC_RA, PINOUT_ENC_RB);

Motor motorL(PINOUT_ML_PWM, PINOUT_ML_DIRF, PINOUT_ML_DIRB);
Motor motorR(PINOUT_MR_PWM, PINOUT_MR_DIRF, PINOUT_MR_DIRB);

enum Mode_t {
    race, test, calib
};
Mode_t mode;

int testNum = 0, calibNum = 0;

#define TIME_INTERVAL 0.003 // in seconds
unsigned long currTime, prevTime;

// TODO: create robot class with robot state variables (position, orientation, velocities, velocities' references...)
// TODO: create control file with functions for coordinated movement (PID on wheels, PID on robot state...)
// TODO: test light sensor (currently not working) and it's calibration routine
// TODO: turn light sensor into object
// TODO: check display scrolling functions
// TODO: config files for spread out constants?

#define BASE_SPEED 0.4
#define KP 5
#define KD 1

void brake() {
    motorL.input = -1;
    motorR.input = -1;
    motorL.update();
    motorR.update();

    delay(400);

    motorL.input = 0;
    motorR.input = 0;
    motorL.update();
    motorR.update();
}

void control() {
    static float prevLinePos = 0;
    static float speedDiff;

    prevLinePos = lineSensors.linePos;

    lineSensors.update();

    if(lineSensors.fullLine || lineSensors.noLine) {
        brake();
        display.printAll("Stop");
        while(true);
    }

    speedDiff = KP*lineSensors.linePos + KD*(lineSensors.linePos-prevLinePos)/TIME_INTERVAL;

    motorL.input = BASE_SPEED - speedDiff;
    motorR.input = BASE_SPEED + speedDiff;

    motorL.update();
    motorR.update();
}

void setup() {
    // Hardware setup
    display.setup();

    display.printAll("Setting up");

    Serial.begin(9600);
    while(!Serial);

    setupLightSensor();
    
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
        static unsigned long t0, t1;
        t0 = micros();
        // control();
        lineSensors.update();
        t1 = micros();
        Serial.println(t1-t0);
        
        break;
    
    case test:
        // Cycle between tests with button presses
        if(btn1.read()) testNum++;
        if(btn2.read()) testNum--;

        switch (testNum) {
        case 0:
            testDisplay(&display, currTime);
            break;
        
        case 1:
            testLightSensor(&display);
            break;
        
        case 2:
            testLineSensors(&lineSensors, &display);
            break;
        
        case 3:
            testEncoders(&encoderL, &encoderR, &display);
            break;

        case 4:
            testMotors(&motorL, &motorR, currTime, &display);
            break;
        
        default:
            // if the testNum is out of bounds, get it back in
            testNum = (testNum + NUM_TESTS) % NUM_TESTS;
            break;
        }

        // Disable motors if their test is not running
        if(testNum != 4) {
            motorL.input = 0;
            motorR.input = 0;
            motorL.update();
            motorR.update();
        }

        break;
    
    case calib:
        // Cycle between calibration routines with button presses
        if(btn1.read()) calibNum++;
        if(btn2.read()) calibNum--;

        switch(calibNum) {
        case 0:
            calibrateLineSensors(&lineSensors, &display);
            break;
        
        case 1:
            calibrateLightSensor(&display);
            break;
        
        case 2:
            calibrateEncoders(&encoderL, &encoderR, &display);
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
