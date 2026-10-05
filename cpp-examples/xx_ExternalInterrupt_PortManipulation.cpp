// Pin definitions
const byte ledPin = 13;        // PB5 (OC0B) - LED pin
const byte interruptPin = 2;   // PD2 (INT0) - input with pullup

volatile byte state = LOW;    // State variable updated in ISR

void setup() {
  // Set LED pin as output (PB5)
  DDRB |= (1 << DDB5);        // Pin 13 (PB5) as OUTPUT
  
  // Set interrupt pin as input with pullup (PD2)
  DDRD &= ~(1 << DDD2);       // Pin 2 (PD2) as INPUT
  PORTD |= (1 << PD2);        // Enable pullup resistor on PD2
  
  // Configure external interrupt INT0 for any logical change
  EICRA = 0;                  // ISC01=0, ISC00=0: Any edge triggers interrupt
  EIFR = (1 << INTF0);        // Clear any pending interrupt flag
  EIMSK |= (1 << INT0);       // Enable external interrupt INT0
}

void loop() {

}

// External Interrupt Request 0 - Pin 2 on Arduino Uno
ISR(INT0_vect) {
  PORTB ^= (1 << PB5);      // Toggle pin 13
}

/*Tilsvarer (nesten) følgende kode:
const byte ledPin = 13;
const byte interruptPin = 2;  // input pin that the interruption will be attached to
volatile byte state = LOW;  // variable that will be updated in the ISR

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}
*/
