//Built-in functions on Arduino to get corresponding bitmask and port for given pin-number
uint8_t pin = 13;
uint8_t bitMask = digitalPinToBitMask(pin);
uint8_t port = digitalPinToPort(pin);
volatile uint8_t *outReg = portOutputRegister(port);

// Set pin HIGH quickly
*outReg |= bitMask;
