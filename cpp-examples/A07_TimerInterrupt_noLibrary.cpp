void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  //Or DDRB |= (1 << PB5);
  
  // Configure Timer1 for CTC mode with auto-reset at OCR1A compare match
  TCCR1A = 0;                    // Normal port operation, OC1A/OC1B disconnected
  TCCR1B = 0b00001101;            // CTC mode with reset at OCR1A, prescaler = 1024 (bits 3:0 = 1101)
  OCR1A = 7813;                  // Compare value for ~0.5 second (pulses to count / perscaler = 0.5 * 16 000 000 / 1024)
  TIMSK1 = 0b00000010;           // Enable TIMER1 COMPA interrupt
}

ISR(TIMER1_COMPA_vect) {        // This matches vector #12 from the table -> what shall happen at scheduled time
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle LED, faster with PORTB ^= _BV(PB5) or PINB = (1 << PB5);
}

void loop() {
  // Your main code runs independently here
  delay(4000);  // Even delays don't affect the precise timing!
}
