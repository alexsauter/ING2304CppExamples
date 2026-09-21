int a;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    a = Serial.read();    //Leser bit-sekvens som ASCII, men tolkes som int
    Serial.println(a);    //Omgjør int-verdien til tilsvarende string ('1' = 49)
  }
}
