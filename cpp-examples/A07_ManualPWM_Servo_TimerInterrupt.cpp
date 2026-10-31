const int SERVO_PIN = 9;    // Servo at pin 9 => PB1 in mask
const int CTRL_PIN = A0;    // Potensiometer as analog input

int pulseWidth = 1500;      //Default puls-width in microseconds

volatile bool state = false;  //Remember state to use in ISR

// Convert microseconds to timer ticks
#define usToTicks(us) ((us * 2))  // We're are going to be at 2MHz (prescaler /8 of 16MHz, set by TCCR1B)

void setup() {
  pinMode(SERVO_PIN, OUTPUT);
  
  // Configure Timer1 for servo control
  TCCR1A = 0;                        // Normal mode, could be TCCR1A = _BV(COM1A0); to toggle OC1A (=pin 9) on Compare Match (hardware auto-toggle)
  TCCR1B = _BV(CS11) | _BV(WGM12);   // Prescaler /8 -> 2MHz timer clock (0.5µs per tick), CTC with auto-reset at match
  TCNT1 = 0;                         // Start from 0 
  
  OCR1A = usToTicks(pulseWidth);     // Calculate match-value for middle possition (start value)
  TIMSK1 |= _BV(OCIE1A);             // Enable output compare A interrupt -> ISR is TIMER1_COMPA_vect
}

void loop() {
  // Pulswidth can be changed during main program
  pulseWidth = map(analogRead(CTRL_PIN), 0, 1023, 1000, 2000); //Adjust for specific servo, 544-2400 can be typical range
}

ISR(TIMER1_COMPA_vect) {
  state = PINB & (1 << (SERVO_PIN - 8)); //Read current state
  PORTB ^= (1 << (SERVO_PIN - 8));       //Toggle SERVO_PIN, here only correct if SERVO_PIN is part of PORTB
  
  //Set new timer value for next trigger after checking actual pin value, updates with current pulseWidth
  if (!state) { // If pin was OFF, we just turned it ON → next turn OFF after pulseWidth
    OCR1A = usToTicks(constrain(pulseWidth, 500, 2500));    //Set counter number to match for current pulseWidth
  } else {      // If pin was ON, we just turned it OFF → wait rest of period (20 ms for servos)
    OCR1A = usToTicks(constrain(20000 - pulseWidth, 500, 19500));
  }
  //TCNT1 = 0;  //Reset counter to start at zero, not necessary when in CTC mode with auto-reset
}
