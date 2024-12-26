#include "motors.hpp"

#define MAX_PWM_OUTPUT 253 // 254 or 255 causes issues with the motors' driver

Motor::Motor(uint8_t pwmPin, uint8_t fDirPin, uint8_t bDirPin) : pwmPin(pwmPin), fDirPin(fDirPin), bDirPin(bDirPin) {
    pinMode(pwmPin, OUTPUT);
    pinMode(fDirPin, OUTPUT);
    pinMode(bDirPin, OUTPUT);

    input = 0;
    update();

    enabled = true;
}

void Motor::setDir() {
    if(!enabled)
        return;
    
    if(input > 0) {
        digitalWrite(bDirPin, 0);
        digitalWrite(fDirPin, 1);
    }
    else {
        digitalWrite(bDirPin, 1);
        digitalWrite(fDirPin, 0);
    }
}

void Motor::update() {
    if(!enabled)
        return;

    // Set the direction pins
    setDir();

    // Get the absolute value of the speed
    float speed = input;
    if(speed < 0)
        speed *= -1;

    // Clip the speed
    if(speed > 1)
        speed = 1;

    // Scale the speed
    speed *= MAX_PWM_OUTPUT;

    // Output the speed
    analogWrite(pwmPin, (int)speed);
}
