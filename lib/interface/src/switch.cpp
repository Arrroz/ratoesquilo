#include "switch.hpp"

Switch::Switch() {
    enabled = false;
}

Switch::Switch(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT);
    enabled = true;
}

bool Switch::read() {
    return enabled && digitalRead(pin);
}
