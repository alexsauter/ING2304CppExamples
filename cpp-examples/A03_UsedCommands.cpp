// === TIMING COMMANDS ===
unsigned long time = millis();    // Returns elapsed milliseconds since Arduino started running
                                    // Useful for non-blocking timing: if(millis() - startTime > delayTime) {}
                                    
unsigned long time = micros();    // Returns elapsed microseconds since Arduino started running  
                                    // More precise than millis(), good for measuring short events

// === PULSE MEASUREMENT ===
unsigned long duration = pulseIn(pin, value);              // Wait for pin to reach 'value', measure how long it stays there
unsigned long duration = pulseIn(pin, value, timeout);     // Same but with timeout in microseconds (prevents infinite waiting)

// Example: Measure button hold time cleanly!
// unsigned long holdTime = pulseIn(BUTTON_PIN, LOW);  // Returns microseconds button was held

// === RANDOM NUMBER GENERATION ===
int randVal = random(maxValue);        // Generate random number between 0 and maxValue-1
int randVal = random(minValue, maxValue); // Generate random number in range [minValue, maxValue)
                                         // Note: Need to call randomSeed() once in setup for true randomness!

randomSeed(seed_value);              // Initialize random number generator (usually called with millis() in setup())

// === CONDITIONAL STATEMENTS ===
if (condition) { 
    // Execute this code if condition is TRUE
} else {
    // Optional: Execute this code if condition is FALSE  
}

while (condition) {
    // Keep executing this loop while condition remains TRUE
    // Useful for waiting/polling! Warning: Can block program execution
}

// === COMPARISON OPERATORS ===
==    // Equal to          
!=    // Not equal to
>     // Greater than      
<     // Less than  
>=    // Greater/equal     
<=    // Less/equal

// === LOGICAL OPERATORS ===
&&    // AND operator: True if BOTH conditions are true
||    // OR operator:  True if AT LEAST ONE condition is true  
!     // NOT operator: Reverses boolean value (!true = false)
