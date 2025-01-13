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

#include "wheel.hpp"
#include "control.hpp"

Switch debugSw(PINOUT_DEBUG_SW);
Dipswitch dipswitch(PINOUT_DIPSWITCH);
Button btn1(PINOUT_BTN1, true), btn2(PINOUT_BTN2, true);

Display display;

LineSensors lineSensors(sizeof(PINOUT_LS_SENSORS)/sizeof(PINOUT_LS_SENSORS[0]), PINOUT_LS_SENSORS, PINOUT_LS_EMITTER_ODD, PINOUT_LS_EMITTER_EVEN);
LightSensor lightSensor;
Encoder encoderL(PINOUT_ENC_LA, PINOUT_ENC_LB);
Encoder encoderR(PINOUT_ENC_RA, PINOUT_ENC_RB);

Motor motorL(PINOUT_ML_PWM, PINOUT_ML_DIRF, PINOUT_ML_DIRB);
Motor motorR(PINOUT_MR_PWM, PINOUT_MR_DIRF, PINOUT_MR_DIRB);

Wheel wheelL(&motorL, &encoderL);
Wheel wheelR(&motorR, &encoderR);

enum Mode_t {
    race, test, calib
};
Mode_t mode;
int testNum = 0, calibNum = 0;

#define TIME_INTERVAL 0.003 // in seconds
float currTime, prevTime;

// TODO: config files for spread out constants?

void setup() {
    // Hardware setup
    display.setup();
    display.print("\nSetting up...");

    lightSensor.setup();

    Serial.begin(9600);
    while(!Serial);

    // Program initialization
    if(!dipswitch[0])
        mode = race;
    else if(!dipswitch[1])
        mode = test;
    else
        mode = calib;

    currTime = millis()/1000.0;

    display.print("\nReady!");
    Serial.println("Ready!");
}

void loop() {
    prevTime = currTime;
    while(currTime - prevTime < TIME_INTERVAL)
        currTime = millis()/1000.0;

    switch(mode) {
    case race:
        static unsigned long t0, t1;
        t0 = micros();
        // motorControl(&motorL, &motorR, &lineSensors, currTime-prevTime);
        // wheelControl(&wheelL, &wheelR, &lineSensors, currTime-prevTime);
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
            testDisplay(&display);
            break;
        
        case 1:
            testLightSensor(&lightSensor, &display);
            break;
        
        case 2:
            testLineSensors(&lineSensors, &display);
            break;
        
        case 3:
            testEncoders(&encoderL, &encoderR, &display);
            break;

        case 4:
            testMotors(&motorL, &motorR, &display);
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
            calibrateLightSensor(&lightSensor, &display);
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
        display.print("\nUnknown mode");
        break;
    }
}
