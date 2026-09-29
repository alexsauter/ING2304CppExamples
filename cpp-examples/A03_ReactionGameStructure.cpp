const int BUTTON_PIN = 2;
const int LED_PIN = 13;
unsigned long reactionTime;

// TODO: Implementer disse funksjonene!
void showReadyState() {
    // TODO: Vis at spillet er klar - kanskje blink LED langsomt?
}

void waitForRandomDelay() {
    // TODO: Vent et tilfeldig antall millisekunder (1000-3000ms)
    // Bruk randomSeed(millis()) i setup() for bedre tilfeldighet!
}

unsigned long measureReactionTime() {
    // TODO: 
    // 1. Ta start-tid før "GO" signal
    // 2. Vise "GO" (slå på LED)  
    // 3. Vent på knappetrykk
    // 4. Ta slutt-tid og beregn reaksjonstid
    return reactionTime;  // Erstatte med faktisk måling
}

void displayResult(unsigned long timeMs) {
    // TODO: Vise resultatet pga Serial.print()
    // Eksempel: "Reaksjonstid: 245 ms"
}

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    randomSeed(millis());  // Viktige for god tilfeldighet!
}

void loop() {
    showReadyState();          // "Get ready..."
    waitForRandomDelay();      // Vent et sekund eller to...
    
    reactionTime = measureReactionTime();  // Spill reaktivt!
    displayResult(reactionTime);           // Vis resultatet
    
    delay(1000);              // Pause før neste runde
}
