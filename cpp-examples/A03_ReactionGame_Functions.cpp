void showReadyState() {
    Serial.println("=== REAKSJONSTEST ===");
    Serial.println("Klar... trykk knapp når du er klar!");
    
    // Blink LED tre ganger for å vise "klar til spel"
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
}

void waitForRandomDelay() {
    int randomDelay = random(1000, 3000);  // 1-3 sekunder
    Serial.println("Vent litt...");
    
    unsigned long startTime = millis();
    while (millis() - startTime < randomDelay) {
        delay(50);  // Unngå "busy waiting"
    }
}

unsigned long measureReactionTime() {
    Serial.println("GO!!!");  
    digitalWrite(LED_PIN, HIGH);  // Signaliser start
    
    unsigned long startTime = micros();  // Mikrosekunder for nøyaktighet!
    
    // Vent på knappetrykk - her kan vi bruke pulseIn() for enkel kode:
    unsigned long reactionMicroseconds = pulseIn(BUTTON_PIN, LOW);
    digitalWrite(LED_PIN, LOW);  // Slå av "GO" signal
    
    return reactionMicroseconds / 1000;  // Konverter til millisekunder
}

// Alternativ versjon uten pulseIn (bruker millis som i tidligere oppgave):
unsigned long measureReactionTime_manual() {
    Serial.println("GO!!!");  
    digitalWrite(LED_PIN, HIGH);
    
    unsigned long startTime = millis();
    
    // Vent på knappetrykk ved hjelp av while-løkke
    while (digitalRead(BUTTON_PIN) == HIGH) {  // Inntil knapp trykkes
        delay(10);  // Liten pause for å ikke "låse opp" CPU-en
    }
    
    unsigned long endTime = millis();
    digitalWrite(LED_PIN, LOW);
    
    return endTime - startTime;
}
