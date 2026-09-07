// === CORE ANALOG READING AND WRITING COMMANDS ===

analogRead(pin);                  // Read value (0..1023) from analog pin corresponding to 0..5 VDC, e.g. from A0
int reading = analogRead(pin);    // Read current analog of pin - returns numbers between 0..1023 on Arduino Uno

pinMode(pin, OUTPUT);             // Set pin as output for driving LEDs, etc.
analogWrite(pin, value);          // Write analog value to output pin, allowed values from 0..255, 500Hz PWM with duty cycle 0..100%

delay(milliseconds);              // Pause program execution for specified milliseconds (blocking!)

// === DEBUGGING COMMANDS ===

Serial.begin(baud_rate);          // Initialize serial communication at specified baud rate (e.g., 9600)
Serial.println(data);             // Print data to Serial Monitor followed by newline
Serial.print(data);               // Print data without adding newline character
