const int buttonPin = 2;     // Pull-up configured internally
bool ledState = false;       // Current state of the LED (off initially)
bool lastButtonState = true; // Previous reading from the button (not pressed yet)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up resistor
}

void loop() {
  bool buttonState = digitalRead(buttonPin); // Read current button state

  // Check for falling edge: was HIGH (not pressed), now LOW (pressed)
  if (lastButtonState == true && buttonState == false) {
    ledState = !ledState;                   // Toggle LED state
    digitalWrite(LED_BUILTIN, ledState);    // Update output immediately
  }

  lastButtonState = buttonState;            // Save current reading for next loop
}
