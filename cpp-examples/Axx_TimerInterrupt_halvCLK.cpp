void setup() {
  // Set pin as OUTPUT first
  pinMode(9, OUTPUT);   // OC1A pin for Timer1 channel A
  
  TCCR1A = 0b01000000;  // Enable OC1A hardware toggle on compare match
                        // (COM1A1:0 = 01 in CTC mode)
  TCCR1B = 0b00001001;  // CTC mode, (001) prescaler = 1 (no prescaler)  
  OCR1A = 0;        // Hver andre puls av CLK (hver gang toggle)
  //OCR1A = 15624;        // ~1 second interval
  TIMSK1 = 0b00000010;  // Optional: also enable interrupt for other uses
}

// No ISR needed! Hardware handles pin toggling automatically
void loop() {
  delay(4000);          // Doesn't affect timing at all
}
