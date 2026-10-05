void setup() {
  // Set pin as OUTPUT first
  pinMode(9, OUTPUT);   // OC1A pin for Timer1 channel A
  
  TCCR1A = 0b01000000;  // Enable OC1A hardware toggle on compare match
                        // COM1A1/COM1A0 (bit 7 og 6): Compare Output Mode for Channel A (controls pin 9 behavior on Uno)
                        // COM1A1:0 = 00 : Normal port operation, OC1A disconnected (default)
                        // COM1A1:0 = 01 : Toggle OC1A on compare match
                        // COM1A1:0 = 10 : Clear OC1A on compare match (non-inverting fast PWM)
                        // COM1A1:0 = 11 : Set OC1A on compare match (inverting mode)
  TCCR1B = 0b00001101;  // CTC mode (01 -> compare with OCR1A), (101) prescaler = 1024  
  OCR1A = 15624;        // ~1 second interval
  TIMSK1 = 0b00000010;  // Optional: also enable interrupt for other uses
}

// No ISR needed! Hardware handles pin toggling automatically
void loop() {
  delay(4000);          // Doesn't affect timing at all
}
