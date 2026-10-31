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

// === MATHEMATICAL UTILITY FUNCTIONS ===
constrain(value, min_limit, max_limit);     // Limits value to stay within [min_limit, max_limit] range
                                            // Returns same type as input (int/long/float/double)
                                            // Prevents out-of-bound values that could damage hardware or break logic

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

// === TIMER1 REGISTERS FOR PWM AND TIMING CONTROL ===
ICR1 = 40000;       // Input Capture Register - Sets period/frequency in Fast PWM modes (Mode 14)
                    // Counter counts from 0 to ICR1, then resets automatically
OCR1A = 3000;       // Output Compare Register A - Controls pulse width/duty cycle
                    // Pin state changes when counter matches this value
TCNT1 = 0;          // Timer/Counter Register - Current count value (read/write)

/* Key Points About Timer1 Registers Used Above:
Core Registers:
• TCCR1A - Timer/Counter Control Register A (waveform generation + output compare)
• TCCR1B - Timer/Counter Control Register B (clock source, waveform mode bits)
• TCNT1 - Timer/Counter Register (current count value)
• OCR1A - Output Compare Register A (pulse width/duty cycle control)
• ICR1 - Input Capture Register (period/frequency setting in Mode 14)
Interrupt System:
• TIMSK1 - Timer/Counter Interrupt Mask Register (enable interrupts)
• TIFR1 - Timer/Counter Interrupt Flag Register (interrupt status flags)
*/
