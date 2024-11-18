#include "motors.hpp"

#define MAX_PWM_OUTPUT 253 // 254 or 255 causes issues with the motors' driver

enum Motor_t {
    left, right
};

bool usingMotors = true;

float lMotorInput, rMotorInput;

void setupMotors() {
    pinMode(PINOUT_M_PWML, OUTPUT);
    pinMode(PINOUT_M_PWMR, OUTPUT);

    pinMode(PINOUT_M_DIRF, OUTPUT);
    pinMode(PINOUT_M_DIRB, OUTPUT);

    lMotorInput = 0;
    rMotorInput = 0;
    updateMotors();
    // moveLR(0, 0);
}

void setMotorDir(bool front) {
    if(front) {
        digitalWrite(PINOUT_M_DIRB, 0);
        digitalWrite(PINOUT_M_DIRF, 1);
    }
    else {
        digitalWrite(PINOUT_M_DIRB, 1);
        digitalWrite(PINOUT_M_DIRF, 0);
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

    // moveLR(-1, -1);
    // delay(400);
    // moveLR(0, 0);
}

// void moveL(float speed) {
//     if(!usingMotors)
//         return;

//     if(speed < 0) {
//         setMotorDir(false);
//         speed *= -1;
//     }
//     else {
//         setMotorDir(true);
//     }

//     if(speed > 1)
//         speed = 1;

//     speed *= MAX_PWM_OUTPUT;

//     analogWrite(PINOUT_M_PWML, (int)speed);
// }

// void moveR(float speed) {
//     if(!usingMotors)
//         return;

//     if(speed < 0) {
//         setMotorDir(false);
//         speed *= -1;
//     }
//     else {
//         setMotorDir(true);
//     }

//     if(speed > 1)
//         speed = 1;
        
//     speed *= MAX_PWM_OUTPUT;

//     analogWrite(PINOUT_M_PWMR, (int)speed);
// }

// void moveLR(float leftSpeed, float rightSpeed) {
//     if(!usingMotors)
//         return;

//     // opposite directions are not currently possible
//     // if they are requested, set the backwards driving motor to stopped
//     // TODO: remove this once different directions are possible
//     if(leftSpeed*rightSpeed < 0) {
//         if(rightSpeed < 0)
//             rightSpeed = 0;
//         else
//             leftSpeed = 0;
//     }

//     moveL(leftSpeed);
//     moveR(rightSpeed);
// }

void updateMotor(Motor_t motor) {
    if(!usingMotors)
        return;

    float speed;
    if(motor == Motor_t::left)
        speed = lMotorInput;
    else if(motor == Motor_t::right)
        speed = rMotorInput;


    setMotorDir((speed > 0));
    
    // get the absolute value of the speed
    if(speed < 0)
        speed *= -1;

    // clip the speed
    if(speed > 1)
        speed = 1;
    
    // scale the speed
    speed *= MAX_PWM_OUTPUT;

    if(motor == Motor_t::left)
        analogWrite(PINOUT_M_PWML, (int)speed);
    else if(motor == Motor_t::right)
        analogWrite(PINOUT_M_PWMR, (int)speed);
}

void updateMotors() {
    if(!usingMotors)
        return;

    // opposite directions are not currently possible
    // if they are requested, set the backwards driving motor to stopped
    // TODO: remove this once different directions are possible
    if(lMotorInput*rMotorInput < 0) {
        if(rMotorInput < 0)
            rMotorInput = 0;
        else
            lMotorInput = 0;
    }

    updateMotor(Motor_t::left);
    updateMotor(Motor_t::right);    
}
