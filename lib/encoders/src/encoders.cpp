#include "encoders.hpp"

/* Transition Table:
00 -> 01 -> 11 -> 10 -> 00 (positive direction)

00 00	0
00 01	+
00 10	-
00 11	0
01 00	-
01 01	0
01 10	0
01 11	+
10 00	+
10 01	0
10 10	0
10 11	-
11 00	0
11 01	-
11 10	+
11 11	0
*/

#define TRANSITION_TABLE (const int8_t[]){0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0}

bool usingEncoders = true;

volatile uint8_t stateL, stateR;
volatile int16_t countL, countR;

float speedL, speedR;

void encodersISR() {
    stateL = (stateL << 2) & 0b1100;
    stateR = (stateR << 2) & 0b1100;
    stateL += (digitalRead(PINOUT_ENC_LA) << 1) + digitalRead(PINOUT_ENC_LB);
    stateR += (digitalRead(PINOUT_ENC_RA) << 1) + digitalRead(PINOUT_ENC_RB);

    countL += TRANSITION_TABLE[stateL];
    countR += TRANSITION_TABLE[stateR];
}

void setupEncoders() {
    pinMode(PINOUT_ENC_LA, INPUT);
    pinMode(PINOUT_ENC_LB, INPUT);
    pinMode(PINOUT_ENC_RA, INPUT);
    pinMode(PINOUT_ENC_RB, INPUT);

    attachPCINT(digitalPinToPCINT(PINOUT_ENC_LA), encodersISR, CHANGE);
    attachPCINT(digitalPinToPCINT(PINOUT_ENC_LB), encodersISR, CHANGE);
    attachPCINT(digitalPinToPCINT(PINOUT_ENC_RA), encodersISR, CHANGE);
    attachPCINT(digitalPinToPCINT(PINOUT_ENC_RB), encodersISR, CHANGE);
    
    stateL = (digitalRead(PINOUT_ENC_LA) << 1) + digitalRead(PINOUT_ENC_LB);
    stateR = (digitalRead(PINOUT_ENC_RA) << 1) + digitalRead(PINOUT_ENC_RB); 
    stateL = (stateL << 2) + stateL;
    stateR = (stateR << 2) + stateR;

    countL = 0;
    countR = 0;

    speedL = 0;
    speedR = 0;
}

void updateEncoderSpeeds(float dt) {
    speedL = countL / (ENC_PULSES_PER_METER * dt);
    countL = 0;
    
    speedR = countR / (ENC_PULSES_PER_METER * dt);
    countR = 0;
}
