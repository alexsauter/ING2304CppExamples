void setup() {
  // Configure Timer1 for CTC mode with OCR1A compare match
  TCCR1A = 0;                    // Normal port operation, OC1A/OC1B disconnected
  TCCR1B = 0b00001011;           // CTC mode, prescaler = 1 (no division)
  OCR1A = 15624;                 // Compare value for ~1 second delay (16MHz/1024 ≈ 1sec)
  TIMSK1 = 0b00000010;           // Enable TIMER1 COMPA interrupt
}

ISR(TIMER1_COMPA_vect) {        // This matches vector #12 from your table!
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle LED, faster with PORTB ^= _BV(PB5);
}

void loop() {
  // Your main code runs independently here
  delay(4000);  // Even delays don't affect the precise timing!
}
