int convert_analog_pin(int pin) {
    if (pin == 34) {
        return 6;
    }
    if (pin == 35) {
        return 7;
    }
    if (pin == 32) {
        return 4;
    }
    if (pin == 33) {
        return 5;
    }
    return pin;
}