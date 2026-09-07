int pot_pin = A0;
int pot_ai = 0; //Potensiometer målt som analog input
long pot_mV = 0; //Potensiometer spenning i milli Volt

void setup() {
  Serial.begin(9600);
}

void loop() {
  pot_ai = analogRead(pot_pin);
  pot_mV = map(pot_ai,0,1023,0,5000); //Alternativt: pot_mV = pot_ai*5000.0/1023.0;
  Serial.print("Analog value: ");
  Serial.println(pot_ai);
  Serial.print("Voltage: ");
  Serial.print(pot_mV);
  Serial.println(" mV");
  delay(1000);
}
