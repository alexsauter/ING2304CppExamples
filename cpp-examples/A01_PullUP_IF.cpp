void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP); // Internal pull-up resistor enabled
}

void loop() {
  if (digitalRead(2) == LOW) {       // Button pressed?
    digitalWrite(LED_BUILTIN, HIGH);  // Turn ON LED
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // Otherwise turn OFF
  }
}
