#include "display.hpp"

#define I2C_DISPLAY_ADDR 0x3C // 0x3D: alternative address for other displays

Display::Display() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT) {}

void Display::setup() {
    if(!begin(SSD1306_SWITCHCAPVCC, I2C_DISPLAY_ADDR)) {
        enabled = false;
        return;
    }
    enabled = true;

    setTextSize(2);
    setTextColor(WHITE);
}

void Display::displayColor(uint16_t color) {
    clearDisplay();
    fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
    display();
}
