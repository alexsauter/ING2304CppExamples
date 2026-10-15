/* Manual PWM using timer/counter match */
const int SERVO_PIN = 9;
const int CTRL_PIN = A0;

int pulseWidth = 1500;   //Start with midle position, if not changed at once

// Convert microseconds to timer ticks
#define usToTicks(us) ((us * 2))  // We're are going to be at 2MHz (prescaler /8 of 16MHz)

void setup() {
  pinMode(SERVO_PIN, OUTPUT);
  
  // Configure Timer1 for servo control
  TCCR1A = 0;              // Normal mode
  TCCR1B = _BV(CS11);      // Prescaler /8 -> 2MHz timer clock (0.5µs per tick)
  TCNT1 = 0;               // Start from 0 
  
  OCR1A = usToTicks(pulseWidth); // Comparevalue given by pulsWidth variable
  
  TIMSK1 |= _BV(OCIE1A);   // Enable output compare A interrupt -> corresponding ISR is TIMER1_COMPA_vect
}

void loop() {
  // pulseWidth can be changed during main program
  pulseWidth = map(analogRead(CTRL_PIN), 0, 1023, 544, 2400);
  
  //Other code will not interfere with PWM output
}

ISR(TIMER1_COMPA_vect) {
  PORTB ^= (1 << (SERVO_PIN - 8)); //Toggle SERVO_PIN, here only correct if SERVO_PIN is part of PORTB
  //Set new time for next trigger - after checking actual pin value
  if ((PORTB & (1 << (SERVO_PIN - 8))) > 0) { //If pin is ON now
    OCR1A = usToTicks(pulseWidth);
  } else {
    OCR1A = usToTicks(20000 - pulseWidth); //Rest of time be OFF
  }
  TCNT1 = 0;  //Reset counter to start at zero
}
