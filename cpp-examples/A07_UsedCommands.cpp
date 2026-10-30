// === TIMERONE LIBRARY COMMANDS ===
#include <TimerOne.h>        // Required library for simplified timer control
                              // Must be installed via Arduino Library Manager

Timer1.initialize(500000);  // Initialize Timer1 with period in microseconds
                            // Sets up CTC mode automatically (500,000 µs = 0.5 seconds)

Timer1.attachInterrupt(handlerFunction);  // Attach function to be called at each interval set by initialize()
                                          // Calls handlerFunction() automatically every period
                                          // Keep interrupt service routines as short as possible!

// === SERVO CONTROL WITH Servo.h LIBRARY ===

#include <Servo.h>              // Required library for standard hobby servo control

Servo myservo;                  // Create a servo object to control a servo

myservo.attach(pin);           // Attach the servo on specified pin to the servo object
                               // Pin must be capable of PWM output (e.g., 3,5,6,9,10,11 on Uno)

myservo.write(angle);          // Set servo position according to angle (0-180 degrees)
                               // Internally converts to appropriate pulse width (typically 544-2400 µs)

myservo.writeMicroseconds(uS); // Set servo position directly by pulse width in microseconds
                               // More precise than write() - accepts values like 1000, 1500, 2000

int pos = myservo.read();      // Read last commanded angle (returns value written with write())

// === MANUAL TIMER1 CONFIGURATION ===
TCCR1A = 0;                    // Reset Timer/Counter Control Register A (normal port operation, OC1A/OC1B disconnected)
                               // Clears all bits for straightforward CTC mode setup

TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12); // Configure Timer/Counter Control Register B:
                                             // WGM12=1 → CTC mode (Clear Timer on Compare Match) with auto-reset at OCR1A
                                             // CS12=1, CS11=0, CS10=1 → Prescaler = 1024 (clk/1024)

OCR1A = 7813;               // Output Compare Register A:
                            // Timer counts from 0 to this value then resets (CTC mode)
                            // For ~0.5s at 16MHz with prescaler 1024: (0.5 * 16,000,000) / 1024 = 7812.5

TIMSK1 |= _BV(OCIE1A);      // Timer/Counter Interrupt Mask Register:
                            // OCIE1A=1 → Enable interrupt when TCNT1 matches OCR1A (output compare A match)

ISR(TIMER1_COMPA_vect) {    // Interrupt Service Routine for TIMER1 COMPA
                            // Runs automatically when TCNT1 reaches OCR1A value
  // User code here - keep as short as possible!
}                           // Vector #12 in ATmega328P interrupt table

/* Key Points About Timer1 Registers Used Above:
• TCCR1A/B – Timer/Counter Control Registers controlling waveform generation & clock prescaling
• WGM bits – Waveform Generation Mode selection; here set for CTC mode with OCR1A as TOP value  
• CS bits – Clock Select determining how much to divide system clock by before feeding timer (here /8)  
• TCNT1 – Current 16-bit counter value incremented every microsecond in our configuration  
• OCR1A – Output Compare Register A holding target count that triggers interrupt when matched  
• TIMSK1 – Timer Interrupt Mask Register enabling/disabling specific interrupts per module feature  
*/
