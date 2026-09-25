// Pin definitions (Uno specific)
#define TRIG_PIN 9    // PB1 = Digital pin 9 on Uno
#define ECHO_PIN 10   // PB2 = Digital pin 10 on Uno

// State machine states
enum SensorState {IDLE, TRIGGERED, MEASURING, COMPLETE};
SensorState currentState = IDLE;

unsigned long startTime = 0;
unsigned long duration = 0;
bool measurementReady = false;

void setup() {
  Serial.begin(9600);
  
  // Configure pins using direct port manipulation (much faster!)
  DDRB |= _BV(DDB1);    // Set PB1 (pin 9) as OUTPUT for trigger
  DDRB &= ~_BV(DDB2);   // Set PB2 (pin 10) as INPUT for echo
  
  PORTB &= ~_BV(PB1);   // Ensure trigger starts LOW
  
  Serial.println("Optimized non-blocking ultrasonic sensor");
}

void loop() {
  switch(currentState) {
    case IDLE:
      // Ultra-fast trigger pulse using direct port manipulation
      PORTB |= _BV(PB1);     // Instant HIGH (no function call overhead!)
      delayMicroseconds(10); // Still accurate for short delays
      PORTB &= ~_BV(PB1);    // Instant LOW again
      currentState = TRIGGERED;
      break;

    case TRIGGERED:
      if ((PINB & _BV(PB2)) != 0) {  // Direct pin read - faster than digitalRead()
        startTime = micros();
        currentState = MEASURING;
      }
      break;

    case MEASURING:
      if ((PINB & _BV(PB2)) == 0) {  // Echo went LOW again
        duration = micros() - startTime;
        currentState = COMPLETE;
        measurementReady = true;
      }
      break;

    case COMPLETE:
      if (measurementReady) {
        float distance_cm = duration / 58.2;
        
        Serial.print("Duration: ");
        Serial.print(duration);
        Serial.println(" µs");
        
        Serial.print("Distance: ");
        Serial.print(distance_cm, 1);
        Serial.println(" cm");

        currentState = IDLE;
        measurementReady = false;
      }
      break;
  }
  
  delay(50); // Non-blocking pause between measurements
}
