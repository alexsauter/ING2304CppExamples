/*
  Interrupt-Driven Ultrasonic Sensor (HC-SR04) Example
  
  Advantages:
  - Precise timing capture via hardware interrupts
  - Non-blocking operation allows concurrent tasks
  - No missed pulse edges due to polling delays
*/

#define TRIG_PIN 9
#define ECHO_PIN 10

// Volatile variables shared between ISR and main code
volatile unsigned long echoStartTime = 0;    // Timestamp when echo goes HIGH
volatile unsigned long echoEndTime = 0;      // Timestamp when echo goes LOW  
volatile bool measurementReady = false;      // Flag indicating new data available
bool trigTurnedOff = true;                   // Track trigger pin state

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);               // Start with trigger low
  pinMode(ECHO_PIN, INPUT);
  
  // Attach interrupt to echo pin - triggers on BOTH edges (CHANGE)
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), handleEchoChange, CHANGE);
  
  Serial.println("Interrupt-driven ultrasonic sensor ready!");
  Serial.println("Measurements will appear every ~100ms");
}

// Interrupt Service Routine - executes instantly when echo pin changes state
void handleEchoChange() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    // Rising edge: start of echo pulse
    echoStartTime = micros();                // Capture exact timestamp
  } else {
    // Falling edge: end of echo pulse  
    echoEndTime = micros();                  // Capture exact timestamp
    measurementReady = true;                 // Signal new data ready
  }
}

void loop() {
  static unsigned long lastTriggerTime = 0;
  const unsigned long triggerInterval = 100; // ms between measurements
  
  unsigned long currentTime = millis();
  
  // Trigger a new measurement at regular intervals (non-blocking)
  if (currentTime - lastTriggerTime >= triggerInterval && trigTurnedOff) {
    sendTriggerPulse();                      // Send 10µs trigger pulse
    lastTriggerTime = currentTime;
  }
  
  // Process completed measurements when ready (also non-blocking)
  if (measurementReady) {
    processMeasurement();                    // Calculate and display distance
    measurementReady = false;                // Clear flag for next reading
  }
  
  // ← Your Arduino can do OTHER work here while waiting!
}

void sendTriggerPulse() {
  digitalWrite(TRIG_PIN, HIGH);            // Start trigger pulse
  delayMicroseconds(10);                    // Hold high for 10µs (datasheet requirement)
  digitalWrite(TRIG_PIN, LOW);             // End trigger pulse immediately
}

void processMeasurement() {
  unsigned long duration = echoEndTime - echoStartTime;  // Calculate pulse width
  
  // Convert to distance: speed of sound = 343 m/s = 29.1 µs/cm round-trip
  float distance_cm = duration / 58.2;      // Division by (29.1 * 2) for round trip
  
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" µs");
  
  Serial.print("Distance: ");
  Serial.print(distance_cm, 1);              // One decimal place precision
  Serial.println(" cm");
}

/* Sample Output:
Duration: 582 µs
Distance: 10.0 cm
Duration: 1164 µs  
Distance: 20.0 cm
*/
