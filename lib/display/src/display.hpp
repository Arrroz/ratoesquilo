#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Wire.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128 // in pixels
#define SCREEN_HEIGHT 64 // in pixels

class Display : public U8G2_SSD1306_128X64_NONAME_F_HW_I2C {
public:
    Display();
    void setup();
    template <typename... Printables>
    void print(Printables... args);

    bool enabled;

private:
    void printBuild();
    template <typename P, typename... Printables>
    void printBuild(P first, Printables... other);
    template <typename... Printables>
    void printBuild(const char *first, Printables... other);

    uint8_t cursor;
};

#include "display.tpp"

#endif
