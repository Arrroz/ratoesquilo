#include "motors.hpp"

#define MAX_PWM_OUTPUT 253 // 254 or 255 causes issues with the motors' driver

enum Motor_t {
    left, right
};

bool usingMotors = true;

float lMotorInput, rMotorInput;

void setupMotors() {
    pinMode(PINOUT_ML_PWM, OUTPUT);
    pinMode(PINOUT_MR_PWM, OUTPUT);

    pinMode(PINOUT_ML_DIRF, OUTPUT);
    pinMode(PINOUT_ML_DIRB, OUTPUT);
    pinMode(PINOUT_MR_DIRF, OUTPUT);
    pinMode(PINOUT_MR_DIRB, OUTPUT);

    lMotorInput = 0;
    rMotorInput = 0;
    updateMotors();
}

void setMotorDir(Motor_t motor, bool front) {
    if(motor == Motor_t::left) {
        if(front) {
            digitalWrite(PINOUT_ML_DIRB, 0);
            digitalWrite(PINOUT_ML_DIRF, 1);
        }
        else {
            digitalWrite(PINOUT_ML_DIRB, 1);
            digitalWrite(PINOUT_ML_DIRF, 0);
        }
    }
    else {
        if(front) {
            digitalWrite(PINOUT_MR_DIRB, 0);
            digitalWrite(PINOUT_MR_DIRF, 1);
        }
        else {
            digitalWrite(PINOUT_MR_DIRB, 1);
            digitalWrite(PINOUT_MR_DIRF, 0);
        }
    }
}

void brake() {
    lMotorInput = -1;
    rMotorInput = -1;
    updateMotors();

    delay(400);

    lMotorInput = 0;
    rMotorInput = 0;
    updateMotors();
}

void updateMotor(Motor_t motor) {
    if(!usingMotors)
        return;

    float speed;
    if(motor == Motor_t::left)
        speed = lMotorInput;
    else if(motor == Motor_t::right)
        speed = rMotorInput;


    setMotorDir(motor, (speed > 0));
    
    // get the absolute value of the speed
    if(speed < 0)
        speed *= -1;

    // clip the speed
    if(speed > 1)
        speed = 1;
    
    // scale the speed
    speed *= MAX_PWM_OUTPUT;

    if(motor == Motor_t::left)
        analogWrite(PINOUT_ML_PWM, (int)speed);
    else if(motor == Motor_t::right)
        analogWrite(PINOUT_MR_PWM, (int)speed);
}

void updateMotors() {
    if(!usingMotors)
        return;

    updateMotor(Motor_t::left);
    updateMotor(Motor_t::right);    
}
