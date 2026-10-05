void setup() {
  pinMode(6,OUTPUT); //Pin 6 kan også brukes av Timer0 direkte, men brukes her som uavhengig pin
  TIMSK0 |= 1 << 1; //Setter EOIE0 -> legger til en match for hver gang teller0 blir 0 (=OCR0A verdi)
}

//Tilhørende ISR = Interrupt Service Routine
ISR(TIMER0_COMPA_vect){
  PORTD ^= 1 << 6;  //Toggle pin 6 (del av Port D)
}

void loop() {
  //Her kan skje noe annet, blir avbrudt hver gang interrupt rutinen kjører
  delay(10000);
}

