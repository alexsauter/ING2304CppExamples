//Må sjekkes, kan være feil i denne:
void setup() {
  pinMode(9, OUTPUT);   // OC1A (Timer1 Channel A)
  pinMode(10, OUTPUT);  // OC1B (Timer1 Channel B)
  
// Fast PWM, 10-bit example:
TCCR1A = 0b10110000;  // COM1A=10 (clear on match), COM1B=11 (set on match)  
TCCR1B = 0b00000101;  // Fast PWM, prescaler = 1024

OCR1A = 300;    // Clear OC1A at count 300
OCR1B = 700;    // Set OC1B at count 700 (both can trigger in same cycle)}

void loop() {
  // Timer handles everything - no CPU required!
}
