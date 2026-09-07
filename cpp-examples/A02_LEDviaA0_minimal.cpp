void setup() {
  pinMode(3, OUTPUT); //Forbered pin 3 som PWM-output
}

void loop() {
  analogWrite(3,analogRead(A0)/4);  //Skriv til pin 3 verdien fra A0 (fototransistor, 0..1023), skalert ned til 0..255
}
