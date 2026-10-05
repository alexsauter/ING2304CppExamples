// === TIMING COMMANDS ===
unsigned long time = millis();    // Returns elapsed milliseconds since Arduino started running
                                    // Useful for non-blocking timing: if(millis() - startTime > delayTime) {}
                                    
unsigned long time = micros();    // Returns elapsed microseconds since Arduino started running  
                                    // More precise than millis(), good for measuring short events

// === PULSE MEASUREMENT (all blokking) ===
unsigned long duration = pulseIn(pin, value);              // Wait for pin to reach 'value', measure how long it stays there
unsigned long duration = pulseIn(pin, value, timeout);     // Same but with timeout in microseconds (prevents infinite waiting)

