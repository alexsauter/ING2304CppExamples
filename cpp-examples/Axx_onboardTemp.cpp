//Function has still to be tested, reading of onboard temp sensor as part of the chip (save between -40 to +85 degrees)
int getTemperature(void) {
  ADMUX = (3 << REFS0) | (8 << MUX0); // 1.1V reference and input = temperature
  delay(10);                          // wait for things to settle down
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (7 << ADPS0); // Enable ADC and start conversion
  while (ADCSRA & (1 << ADSC));       // wait for completion
  return (ADCW * 100L - 32431) / 122; // Convert to degrees Celsius
}
