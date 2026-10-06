// Trigger-step: Send (at least) 10µs HIGH pulse to trigger measurement
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);           // Critical timing - must be at least 10µs
digitalWrite(TRIG_PIN, LOW);
