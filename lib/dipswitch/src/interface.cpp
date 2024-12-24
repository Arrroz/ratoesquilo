#include "interface.hpp"

bool dipswitch[DIPSWITCH_NPINS];

void setupInterface() {
    for(uint8_t i = 0; i < DIPSWITCH_NPINS; i++)
        pinMode(PINOUT_DIPSWITCH[i], INPUT);

    pinMode(PINOUT_BTN1, INPUT);
    pinMode(PINOUT_BTN2, INPUT);

    pinMode(PINOUT_DEBUG_SW, INPUT);
}

void readDipswitch() {
    for(uint8_t i = 0; i < DIPSWITCH_NPINS; i++)
        dipswitch[i] = digitalRead(PINOUT_DIPSWITCH[DIPSWITCH_NPINS-1-i]);
}
