const int BUTTON_PIN = 2;
const int LED_PIN = 13;  // Intern LED

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {  // Knapp trykket (aktiv lav)
        digitalWrite(LED_PIN, HIGH);       // Slå på LED for å vise aktivitet
        
        unsigned long startTime = millis();  // Ta start-tid
        
        while (digitalRead(BUTTON_PIN) == LOW) {  // Vent til knapp slippeppes!
            delay(10);  // Liten forsinkelse for å unngå "busy waiting"
        }
        
        unsigned long endTime = millis();    // Ta slutt-tid
        unsigned long duration = endTime - startTime;  // Beregn varighet
        
        Serial.print("Knapp trykket i: ");
        Serial.print(duration);
        Serial.println(" ms");
        
        digitalWrite(LED_PIN, LOW);          // Slå av LED
    }
}
