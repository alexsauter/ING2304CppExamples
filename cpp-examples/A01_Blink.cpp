void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, true); //Bruk true, eller alternativt 1 eller HIGH for "on"
  delay(3000);   //Venter i 3 sekunder
  digitalWrite(LED_BUILTIN, false); //Bruk false, eller alternativt 0 eller LOW for "off"
  delay(3000);   //Venter i 3 sekunder
}
