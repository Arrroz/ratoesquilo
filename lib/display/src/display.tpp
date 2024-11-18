extern bool usingDisplay;

inline void _displayPrintBuild() {}

template <typename P, typename... Printables>
void _displayPrintBuild(P first, Printables... other) {
    if(!usingDisplay)
        return;
    
    display.print(first);
    _displayPrintBuild(other...);
}

template <typename... Printables>
void displayPrint(Printables... args) {
    if(!usingDisplay)
        return;
    
    display.clearDisplay();
    display.setCursor(0, 10);
    _displayPrintBuild(args...);
    display.display();
}
