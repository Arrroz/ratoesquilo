inline void Display::printBuild() {}

template <typename P, typename... Printables>
void Display::printBuild(P first, Printables... other) {
    if(!enabled)
        return;
    
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C::print(first);
    printBuild(other...);
}

template <typename... Printables>
void Display::printBuild(const char *first, Printables... other) {
    if(!enabled)
        return;

    uint16_t i = 0;
    while(first[i] != '\0') {
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C::print(first[i]);

        if(first[i] == '\n') {
            cursor += 20;
            setCursor(0, cursor);
        }

        i++;
    }
    
    printBuild(other...);
}

template <typename... Printables>
void Display::print(Printables... args) {
    if(!enabled)
        return;
    
    cursor = 20;
    
    firstPage();
    do {
        setCursor(0, cursor);
        printBuild(args...);
    } while(nextPage());
}
