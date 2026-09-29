const int BUTTON_PIN = 2;
const int LED_PIN = 13;

bool lastButtonState = HIGH;    // Starter med pull-up aktivert
bool currentButtonState;
unsigned long pressStartTime = 0;
bool measuring = false;         // Flag for å holde styr på tilstanden

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    currentButtonState = digitalRead(BUTTON_PIN);  // Les knappens nåværende tilstand
    
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        // Falling edge - START måling!
        pressStartTime = millis();
        measuring = true;
        digitalWrite(LED_PIN, HIGH);  // Vis at vi måler
        Serial.println("Måler...");   // Debug info
    }
    
    if (lastButtonState == LOW && currentButtonState == HIGH) {
        // Rising edge - SLUTT måling!
        unsigned long pressDuration = millis() - pressStartTime;
        digitalWrite(LED_PIN, LOW);  // Slå av LED
        
        Serial.print("Knapp trykket i: ");
        Serial.print(pressDuration);
        Serial.println(" ms");
    }
    
    lastButtonState = currentButtonState;  // Oppdater for neste iterasjon!
}
