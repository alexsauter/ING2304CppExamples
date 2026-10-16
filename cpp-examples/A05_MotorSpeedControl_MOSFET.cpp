void setup() {
  pinMode(9,OUTPUT);
}

void loop() {
  analogWrite(9,analogRead(A0)/4); //Potensiometer ved A0 styrer farten til motoren på pin 9
}
