#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <Arduino.h>
#include <connections.hpp>

#define DIPSWITCH_NPINS 4
extern bool dipswitch[DIPSWITCH_NPINS];

void setupInterface();
void readDipswitch();

#endif
