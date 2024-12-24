#ifndef ENCODER_H_
#define ENCODER_H_

#include <Arduino.h>
#include <PinChangeInterrupt.h>

class Encoder {
public:
    Encoder(uint8_t pinA, uint8_t pinB);
    void updateSpeed(float dt = 1);

    float speed;
    volatile int16_t count;
    volatile uint8_t state;

    uint8_t pinA, pinB;

    bool enabled;
};

#endif
