#include "display.hpp"

#define I2C_DISPLAY_ADDR 0x3C // 0x3D: alternative address for other displays

bool usingDisplay = true;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupDisplay() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, I2C_DISPLAY_ADDR)) {
        usingDisplay = false;
        return;
    }

    display.setTextSize(2);
    display.setTextColor(WHITE);
}

void displayColor(uint16_t color) {
    display.clearDisplay();
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
    display.display();
}
