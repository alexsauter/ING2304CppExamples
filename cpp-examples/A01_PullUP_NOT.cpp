void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP); // Internal pull-up resistor enabled
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(2)); // Invert logic
}
