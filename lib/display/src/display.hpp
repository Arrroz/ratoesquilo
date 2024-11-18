#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <connections.hpp>

#define SCREEN_WIDTH 128 // in pixels
#define SCREEN_HEIGHT 64 // in pixels
#define DISPLAY_MAX_CHARS 11 // for a text size of 2

// Display is monochrome ;(
// #define RED     0b1111100000000000
// #define GREEN   0b0000011111100000
// #define BLUE    0b0000000000011111
// #define YELLOW  0b1111111111100000

extern Adafruit_SSD1306 display;

void setupDisplay();

template <typename... Printables>
void displayPrint(Printables... args);

void displayColor(uint16_t color);

#include "display.tpp"

#endif
