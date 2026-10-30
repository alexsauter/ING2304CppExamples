//Servo on OC1A = pin 9
const int CTRL_PIN = A0;    // Potensiometer as analog input on A0

int pulseWidth = 1500;      //Default puls-width in microseconds

// Convert microseconds to timer ticks
#define usToTicks(us) ((us * 2))  // We're are going to be at 2MHz (prescaler /8 of 16MHz, set by TCCR1B)

void setup() {
  pinMode(9, OUTPUT);    // For setting OC1A = pin 9 as output (not strictly necessary here)
  
  // Configure Timer1 for servo control - fast PWM
  TCCR1A = _BV(COM1A1) | _BV(WGM11);              // Clear OC1A on compare match
  TCCR1B = _BV(CS11) | _BV(WGM13) | _BV(WGM12);   // Prescaler /8 -> 2MHz timer clock (0.5µs per tick), Fast PWM, reset at ICR1
  TCNT1 = 0;                                      // Start from 0 (to be clean)
  
  OCR1A = usToTicks(pulseWidth);   // Calculate match-value for middle possition (start value) -> clears OC1A to LOW
  ICR1 = usToTicks(20000);         // Calculate match-value for reset to new puls -> sets OC1A to HIGH

  TIMSK1 |= _BV(TOIE1);             // Enable overlow interrupt -> ISR is TIMER1_OVF_vect, only to update pulsWidth
}

void loop() {
  // Pulswidth can be changed during main program
  pulseWidth = map(analogRead(CTRL_PIN), 0, 1023, 550, 2250);   //Adjust for specific servo, 544-2400 can be typical range
}

ISR(TIMER1_OVF_vect) {
  OCR1A = usToTicks(pulseWidth);    //Set counter number to match for current pulseWidth
}
