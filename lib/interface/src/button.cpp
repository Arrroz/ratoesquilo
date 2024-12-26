#include "button.hpp"

#define BTN_COUNT4TRANSITION 1

Button::Button(uint8_t pin, bool reversed) : pin(pin), reversed(reversed) {
    pinMode(pin, INPUT);
    state = 0;
    count = 0;
}

bool Button::read() {
    pressed = (reversed != (bool)digitalRead(pin));

    switch(state) {
    // low
    case 0:
        if(pressed) {
            count = 1;
            state = 1;
        }

        break;
    
    // rising
    case 1:
        if(pressed) count++;
        else count--;

        if(count >= BTN_COUNT4TRANSITION) {
            state = 2;
            return true;
        }
        else if(count == 0)
            state = 0;

        break;
    
    // high
    case 2:
        if(!pressed) {
            count = 1;
            state = 3;
        }

        break;

    // falling
    case 3:
        if(!pressed) count++;
        else count--;

        if(count >= BTN_COUNT4TRANSITION)
            state = 0;
        else if(count == 0)
            state = 2;
        
        break;
    
    default:
        break;
    }

    return false;
}
