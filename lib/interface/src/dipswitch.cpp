#include "dipswitch.hpp"

Dipswitch::Dipswitch(const uint8_t pins[]) {
    for(uint8_t i = 0; i < DIPSWITCH_NPINS; i++)
        switches[i] = Switch(pins[i]);
}

bool Dipswitch::operator[](uint8_t i) {
    return switches[i].read();
}
