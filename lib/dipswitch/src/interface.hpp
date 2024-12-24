#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <Arduino.h>
#include <connections.hpp>

#define DIPSWITCH_NPINS 4
extern bool dipswitch[DIPSWITCH_NPINS];

#define NUM_BUTTONS 2
extern bool btnTriggered[NUM_BUTTONS];

void setupInterface();
void readDipswitch();
void readButton(uint8_t btnNum);
void readButtons();

#endif
