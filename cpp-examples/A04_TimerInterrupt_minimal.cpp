#include <TimerOne.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize the timer for 500,000 microseconds (0.5 seconds)
  Timer1.initialize(500000); 
  
  // Attach the interrupt service routine (ISR)
  Timer1.attachInterrupt(blinkISR); 
}

void loop() {
  // Main code runs freely here without blocking
}

void blinkISR() {
  // Toggle the built-in LED
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //Alternativt: PORTB ^= (1 << 5); eller PORTB ^= _BV(PB5); (~ 16-20x kortere interrupt)
}
