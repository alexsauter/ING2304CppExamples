//Kommunikasjon via seriell buss (til PC via USB eller annen Arduino via pin 0 og pin 1)
//For at pin 0 og pin 1 brukes må ikke USB være koblet til

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Send potensiometer-verdi (0..255) via pin 1 (TX, med pin 0 som RX)
  Serial.println(analogRead(A0));
  delay(100);
}
