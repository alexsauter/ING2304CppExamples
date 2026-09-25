float readDistanceFast() {
    PORTB |= _BV(PB1);     // Trigger HIGH
    delayMicroseconds(10);
    PORTB &= ~_BV(PB1);    // Trigger LOW
    
    while ((PINB & _BV(PB2)) == 0);  // Wait for echo start - BLOCKING!
    unsigned long start = micros();
    
    while ((PINB & _BV(PB2)) != 0);  // Wait for echo end - BLOCKING!
    return (micros() - start) / 58.2;
}

// Usage:
void loop() {
  float distance = readDistanceFast();  // Blocks until complete!
  Serial.println(distance);
}
