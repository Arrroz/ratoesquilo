#ifndef ENCODER_H_
#define ENCODER_H_

#include <Arduino.h>
#include <connections.hpp>
#include <PinChangeInterrupt.h>

#define ENC_PULSES_PER_METER 1575

extern float speedL, speedR;

void setupEncoders();
void updateEncoderSpeeds(float dt = 1);

#endif
