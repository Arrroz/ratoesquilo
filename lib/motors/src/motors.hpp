#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

class Motor {
public:
    Motor(uint8_t pwmPin, uint8_t fDirPin, uint8_t bDirPin);
    void setDir();
    void stop();
    void update();

    float input;

    bool enabled;

private:
    uint8_t pwmPin, fDirPin, bDirPin;
};

#endif
