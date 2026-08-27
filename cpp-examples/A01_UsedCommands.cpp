// === CORE BUTTON READING COMMANDS ===

pinMode(pin, INPUT);              // Set pin as input (floating - needs external pull-up/down)
pinMode(pin, INPUT_PULLUP);       // Set pin as input with internal ~50kΩ pull-up resistor to VCC
pinMode(pin, OUTPUT);             // Set pin as output for driving LEDs, etc.

digitalWrite(pin, HIGH);          // Write logic high (VCC) to output pin or enable internal pull-up in INPUT mode
digitalWrite(pin, LOW);           // Write logic low (GND) to output pin
bool reading = digitalRead(pin);   // Read current digital state of pin - returns HIGH(1) or LOW(0)

delay(milliseconds);              // Pause program execution for specified milliseconds (blocking!)
unsigned long now = millis();     // Returns elapsed time since Arduino started in milliseconds (non-blocking timing)

// === DEBUGGING COMMANDS ===

Serial.begin(baud_rate);          // Initialize serial communication at specified baud rate (e.g., 9600)
Serial.println(data);             // Print data to Serial Monitor followed by newline
Serial.print(data);               // Print data without adding newline character

// === LOGIC VALUES & CONSTANTS ===

HIGH                                // Digital logic HIGH (typically +5V or +3.3V) - equals 1, true
LOW                                 // Digital logic LOW (0V/GND) - equals 0, false
true / false                        // Boolean values equivalent to 1/0 respectively

// === TIMING COMPARISON EXAMPLE ===

if (millis() - lastTime > debounceDelay) { }  // Non-blocking timer check using millis()

// === BOOLEAN DATA TYPES ===
bool buttonPressed = digitalRead(BUTTON_PIN);    // HIGH(1) or LOW(0) stored as boolean
bool ledState = false;                           // Initialize as OFF
const bool DEBUG_MODE = true;                    // Compile-time constant

void loop() {
    buttonPressed = digitalRead(BUTTON_PIN);
    
    if (buttonPressed) {                        // Direct boolean check - much cleaner!
        Serial.println("Button pressed!");      // No need for == HIGH comparison
    } else {
        ledState = !ledState;                   // Toggle state using NOT operator
    }
}
