#include "display.hpp"

Display::Display() : U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0) {}

void Display::setup() {
    begin();
    setFont(u8g2_font_heavybottom_tr);
    enabled = true;
}
