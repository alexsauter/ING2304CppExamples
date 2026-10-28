void setup() {
  DDRB |= (1 << PB5);  //Bruk LED_BUILTIN

  //Set opp pin 2 som external interrupt
  EICRA = 0B00000001;
  EIFR = 0B00000001;
  EIMSK |= 0B00000001;

}

void loop() {
  // noe annet
}

ISR(INT0_vect){
  PINB |= (1 << PB5);  // Toggel LED_BUILTIN når CHANGE ved pin 2
}
