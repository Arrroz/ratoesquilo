#include "encoders.hpp"

#define ENC_PULSES_PER_METER 1575

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

// WARNING: this is ugly (declaration inside the library),
// but required for the ISR to handle both encoders at once
extern Encoder encoderL, encoderR;

// WARNING: assumes the existence of 2 encoders (left & right) to prevent overhead from loops
void encodersISR() {
    encoderL.state = (encoderL.state << 2) & 0b1100;
    encoderR.state = (encoderR.state << 2) & 0b1100;
    encoderL.state += (digitalRead(encoderL.pinA) << 1) + digitalRead(encoderL.pinB);
    encoderR.state += (digitalRead(encoderR.pinA) << 1) + digitalRead(encoderR.pinB);

    encoderL.count += TRANSITION_TABLE[encoderL.state];
    encoderR.count += TRANSITION_TABLE[encoderR.state];
}

Encoder::Encoder() {
    enabled = false;
}

Encoder::Encoder(uint8_t pinA, uint8_t pinB) : pinA(pinA), pinB(pinB) {
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

    attachPCINT(digitalPinToPCINT(pinA), encodersISR, CHANGE);
    attachPCINT(digitalPinToPCINT(pinB), encodersISR, CHANGE);

    speed = 0;
    count = 0;

    state = (digitalRead(pinA) << 1) + digitalRead(pinB);
    state = (state << 2) + state;

    enabled = true;
}

void Encoder::updateSpeed(float dt) {
    if(!enabled)
        return;

    speed = count / (ENC_PULSES_PER_METER * dt);
    count = 0;
}
