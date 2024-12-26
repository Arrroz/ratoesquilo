#ifndef SWITCH_H_
#define SWITCH_H_

#include <Arduino.h>

class Switch {
public:
    Switch();
    Switch(uint8_t pin);
    bool read();

    bool enabled;

private:
    uint8_t pin;
};

#endif
