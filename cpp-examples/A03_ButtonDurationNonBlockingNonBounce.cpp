// Legg til debounce-logikk for mer robust kode:
const unsigned long DEBOUNCE_DELAY = 50;  // ms

static unsigned long lastDebounceTime = 0;
static bool stableButtonState = HIGH;

void loop() {
    bool reading = digitalRead(BUTTON_PIN);
    
    if (reading != lastButtonState) {
        lastDebounceTime = millis();  // Nullstill timer ved endring
    }
    
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // Endringen er stabil nok!
        if (reading != stableButtonState) {
            stableButtonState = reading;
            
            // Bruk stableButtonState i logikken over...
            handleButtonPress(stableButtonState);
        }
    }
    
    lastButtonState = reading;  // Lagre for neste runde
}

void handleButtonPress(bool newState) {
    static unsigned long pressStartTime = 0;
    
    if (newState == LOW && stableButtonState == HIGH) {  // Trykk start
        pressStartTime = millis();
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Måler...");
    } else if (newState == HIGH && stableButtonState == LOW) {  // Trykk slutt
        unsigned long duration = millis() - pressStartTime;
        digitalWrite(LED_PIN, LOW);
        
        Serial.print("Varighet: ");
        Serial.print(duration);
        Serial.println(" ms");
    }
}
