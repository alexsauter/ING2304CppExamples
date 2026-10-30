// === TIMING COMMANDS ===
unsigned long time = millis();    // Returns elapsed milliseconds since Arduino started running
                                    // Useful for non-blocking timing: if(millis() - startTime > delayTime) {}
                                    
unsigned long time = micros();    // Returns elapsed microseconds since Arduino started running  
                                    // More precise than millis(), good for measuring short events

delay(milliseconds);              // Pause program execution for specified milliseconds (blocking!)
delayMicroseconds(microseconds);  // Pause program execution for sepcified microseconds (blocking!)

// === DIGITAL READ AND WRITE (port manipulation) ===
DDRB |= (1 << PB5);        // Pin 13 (PB5) as OUTPUT

DDRD &= ~(1 << PD2);       // Pin 2 (PD2) as INPUT
PORTD |= (1 << PD2);        // Enable pullup resistor on PD2 (pin 2)

PORTB |= (1 << PB5);      // Turn pin 13 to HIGH
PORTB &= ~(1 << PB5);      // Turn pin 13 to LOW
PORTB ^= (1 << PB5);      // Toggle pin 13

PINB |= (1 << PB5);      // Toggle pin 13

bool pin_value = PIND & (1 << PD2);  //Read value of pin 2

// === EXTERNAL INTERRUPT (port manipulation) ===
EICRA = 0B00000001;         // ISC01=0, ISC00=1: Any change on INT0 (=pin 2) triggers interrupt
EIFR = 0B00000001;        // Clear any pending interrupt flag for INT0 (optional, resets automatically when ISR is run)
EIMSK |= 0B00000001;       // Enable external interrupt INT0

ISR(INT0_vect) {            // ISR that runs upon trigger condition for INT0
  //do something
}

// === EXTERNAL INTERRUPT (with Arduino functions) ===
volatile bool state;  //Variables changed during interrupt have to be of type volatile!

void setup() {
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), changeState, CHANGE);  // Start interrupt routine based on pin ECHO_PIN changing -> run function changeState
                                                                          // Mode: LOW, CHANGE, RISING, FALLING
                                                                          // See also: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
}

void loop() {
  if (state) {
    //do something
  }
}

//Interrupt Service Routine (ISR) triggered by CHANGE of ECHO_PIN
//Keep as short as possible!
void changeState() {
  state = !state;
}
