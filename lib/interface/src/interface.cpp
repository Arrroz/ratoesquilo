#include "interface.hpp"

bool dipswitch[DIPSWITCH_NPINS];

#define BTN_COUNT4TRANSITION 1
bool btnPressed[NUM_BUTTONS];
uint8_t btnState[NUM_BUTTONS];
uint8_t btnCount[NUM_BUTTONS];
bool btnTriggered[NUM_BUTTONS];

void setupInterface() {
    for(uint8_t i = 0; i < DIPSWITCH_NPINS; i++) {
        pinMode(PINOUT_DIPSWITCH[i], INPUT);
        dipswitch[i] = false;
    }

    for(uint8_t i = 0; i < NUM_BUTTONS; i++) {
        pinMode(PINOUT_BTNS[i], INPUT);
        btnState[i] = 0;
        btnCount[i] = 0;
        btnTriggered[i] = false;
    }

    pinMode(PINOUT_DEBUG_SW, INPUT);
}

void readDipswitch() {
    for(uint8_t i = 0; i < DIPSWITCH_NPINS; i++)
        dipswitch[i] = digitalRead(PINOUT_DIPSWITCH[DIPSWITCH_NPINS-1-i]);
}

void readButton(uint8_t btnNum) {
    btnPressed[btnNum] = !digitalRead(PINOUT_BTNS[btnNum]);

    switch(btnState[btnNum]) {
    // low
    case 0:
        if(btnPressed[btnNum]) {
            btnCount[btnNum] = 1;
            btnState[btnNum] = 1;
        }

        break;

    // rising
    case 1:
        if(btnPressed[btnNum])
            btnCount[btnNum]++;
        else
            btnCount[btnNum]--;

        if(btnCount[btnNum] >= BTN_COUNT4TRANSITION) {
            btnState[btnNum] = 2;
            btnTriggered[btnNum] = true;
        }
        else if(btnCount[btnNum] == 0)
            btnState[btnNum] = 0;

        break;

    // high
    case 2:
        btnTriggered[btnNum] = false;

        if(!btnPressed[btnNum]) {
            btnCount[btnNum] = 1;
            btnState[btnNum] = 3;
        }

        break;

    // falling
    case 3:
        if(!btnPressed[btnNum])
            btnCount[btnNum]++;
        else
            btnCount[btnNum]--;

        if(btnCount[btnNum] >= BTN_COUNT4TRANSITION)
            btnState[btnNum] = 0;
        else if(btnCount[btnNum] == 0)
            btnState[btnNum] = 2;

        break;
    
    default:
        break;
    }
}

void readButtons() {
    for(uint8_t i = 0; i < NUM_BUTTONS; i++)
        readButton(i);
}
