#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>

class Button {
public:
    Button(uint8_t pin, bool reversed = false);
    bool read();

private:
    bool pressed;
    uint8_t state;
    uint8_t count;

    uint8_t pin;
    bool reversed;
};

#endif
