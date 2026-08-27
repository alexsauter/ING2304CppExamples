void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT); // External resistor pulls down to GND when open
}

void loop() {
  digitalWrite(LED_BUILTIN, digitalRead(2));
}
