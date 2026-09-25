#define TRIG_PIN 9
#define ECHO_PIN 10

// State definitions for our sensor state machine
enum SensorState {
  IDLE,          // Ready to trigger next measurement
  TRIGGERED,     // Waiting for echo to start (pin goes HIGH)
  MEASURING,     // Echo is HIGH - waiting for it to go LOW again
  COMPLETE       // Measurement done - ready to report result
};

SensorState currentState = IDLE;
unsigned long startTime = 0;
unsigned long duration = 0;
bool measurementReady = false;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  
  Serial.println("Non-blocking ultrasonic sensor demo");
}

void loop() {
  // Handle current state
  switch (currentState) {
    case IDLE:
      // Ready to start new measurement - trigger now!
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);           // Still blocking for this brief moment
      digitalWrite(TRIG_PIN, LOW);
      currentState = TRIGGERED;        // Move to next state immediately
      break;

    case TRIGGERED:
      // Waiting for echo pin to go HIGH (start of pulse)
      if (digitalRead(ECHO_PIN) == HIGH) {
        startTime = micros();          // Record when measurement started
        currentState = MEASURING;
      }
      break;

    case MEASURING:
      // Echo is high - waiting for it to go LOW again
      if (digitalRead(ECHO_PIN) == LOW) {
        duration = micros() - startTime;   // Calculate pulse width
        currentState = COMPLETE;
        measurementReady = true;            // Signal that data is ready
      }
      break;

    case COMPLETE:
      // Process the result and prepare for next cycle
      if (measurementReady) {
        float distance_cm = duration / 58.2;
        
        Serial.print("Duration: ");
        Serial.print(duration);
        Serial.println(" µs");
        
        Serial.print("Distance: ");
        Serial.print(distance_cm, 1);
        Serial.println(" cm");

        // Reset for next measurement cycle
        currentState = IDLE;              // Go back to idle state
        measurementReady = false;         // Clear flag
      }
      break;
  }
  
  delay(50);  // Small gap between measurements (non-blocking!)
}
