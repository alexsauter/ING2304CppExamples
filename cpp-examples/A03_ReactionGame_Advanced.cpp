const int MAX_ROUNDS = 5;
unsigned long reactionTimes[MAX_ROUNDS];
int roundNumber = 0;

void loop() {
    if (roundNumber < MAX_ROUNDS) {
        showReadyState();
        waitForRandomDelay();
        
        unsigned long timeTaken = measureReactionTime();
        displayResult(timeTaken);
        
        reactionTimes[roundNumber] = timeTaken;  // Lagre for statistikk
        roundNumber++;
        
        delay(1500);  // Pause mellom runder
    } else {
        showStatistics();  // Vis gjennomsnitt, min, max osv.
        resetGame();       // Klar for ny spilltur
    }
}

void displayResult(unsigned long timeMs) {
    Serial.print("Reaksjonstid: ");
    Serial.print(timeMs);
    Serial.println(" ms");
}

void showStatistics() {
    unsigned long sum = 0;
    unsigned long minTime = reactionTimes[0];
    unsigned long maxTime = reactionTimes[0];
    
    for (int i = 0; i < MAX_ROUNDS; i++) {
        sum += reactionTimes[i];
        if (reactionTimes[i] < minTime) minTime = reactionTimes[i];
        if (reactionTimes[i] > maxTime) maxTime = reactionTimes[i];
    }
    
    float average = (float)sum / MAX_ROUNDS;
    
    Serial.println("\n=== STATISTIKK ===");
    Serial.print("Gjennomsnitt: "); Serial.print(average); Serial.println(" ms");
    Serial.print("Best: "); Serial.print(minTime); Serial.println(" ms");
    Serial.print("Dårligst: "); Serial.print(maxTime); Serial.println(" ms");
}

void resetGame() {
    roundNumber = 0;
    delay(3000);  // Tre sekunder pause før ny spilltur
}
