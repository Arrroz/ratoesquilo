#ifndef DIPSWITCH_H_
#define DIPSWITCH_H_

#include <Arduino.h>
#include "switch.hpp"

#define DIPSWITCH_NPINS 4

class Dipswitch {
public:
    Dipswitch(const uint8_t pins[]);
    bool operator[](uint8_t i);

private:
    Switch switches[DIPSWITCH_NPINS];
};

#endif
