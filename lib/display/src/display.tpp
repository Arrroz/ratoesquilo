inline void Display::printBuild() {}

template <typename P, typename... Printables>
void Display::printBuild(P first, Printables... other) {
    if(!enabled)
        return;
    
    print(first);
    printBuild(other...);
}

template <typename... Printables>
void Display::printAll(Printables... args) {
    if(!enabled)
        return;
    
    clearDisplay();
    setCursor(0, 10);
    printBuild(args...);
    display();
}
