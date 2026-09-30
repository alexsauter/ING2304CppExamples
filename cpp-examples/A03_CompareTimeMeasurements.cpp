// Erstatte den manuelle measureReactionTime() med en versjon som bruker pulseIn():
unsigned long measureReactionTime_pulseIn() {
    Serial.println("GO!!!");  
    digitalWrite(LED_PIN, HIGH);  // Signaliser start
    
    unsigned long startTime = micros();  // For sammenligning!
    
    // Her er det enkle pulseIn()-versjonen:
    unsigned long reactionMicroseconds = pulseIn(BUTTON_PIN, LOW);  // Blokker til knapp trykkes!
    
    digitalWrite(LED_PIN, LOW);  // Slå av "GO" signal
    
    Serial.print("Manuell måling ville gitt: ");
    Serial.print(micros() - startTime);
    Serial.println(" mikrosekunder");
    
    return reactionMicroseconds / 1000;  // Konverter til millisekunder
}

// Sammenligningsfunksjon for å vise forskjellen:
void compareTimingMethods() {
    Serial.println("\n=== SAMMENLIGNING AV MÅTEMÅTER ===");
    
    // Metode 1: Manuell med millis() (ikke-blokkerende)
    unsigned long start1 = micros();
    while(digitalRead(BUTTON_PIN) == HIGH) { delay(5); }  // Unngå busy-wait
    unsigned long manualTime = micros() - start1;
    
    Serial.print("Manuell metode: ");
    Serial.print(manualTime / 1000.0);
    Serial.println(" ms");
    
    delay(2000);  // Pause før neste test
    
    // Metode 2: pulseIn() (blokkerende men enkel!)
    digitalWrite(LED_PIN, HIGH);
    unsigned long start2 = micros();
    unsigned long autoTime = pulseIn(BUTTON_PIN, LOW);  // Automatisk!
    digitalWrite(LED_PIN, LOW);
    
    Serial.print("pulseIn() metode: ");
    Serial.print(autoTime / 1000.0);
    Serial.println(" ms");
}
