#define TRIG_PIN 9    // Connect HC-SR04 VCC to Arduino 5V, GND to GND
#define ECHO_PIN 10   // Trig -> Pin 9, Echo -> Pin 10

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);  // Trigger pin sends the ultrasonic burst
  pinMode(ECHO_PIN, INPUT);   // Echo pin receives the reflected signal
}

void loop() {
  // Step 1: Send 10µs trigger pulse (per HC-SR04 datasheet)
  digitalWrite(TRIG_PIN, LOW);   
  delayMicroseconds(2);          // Small settling time
  digitalWrite(TRIG_PIN, HIGH);  
  delayMicroseconds(10);         // Critical 10µs minimum pulse width
  digitalWrite(TRIG_PIN, LOW);

  // Step 2: Measure echo duration (time for sound to travel round-trip)
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout (~5m range)

  // Step 3: Process results
  if (duration == 0) {
    Serial.println("Timeout - no object detected within range");
  } else {
    // Physics explanation: Sound travels at ~343 m/s in air
    // That's ~29.1 µs per cm, but we divide by 58.2 because it's round-trip!
    float distance_cm = duration / 58.2;     
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    
    // Optional: Show raw timing for advanced understanding
    Serial.print("Raw time: ");
    Serial.print(duration);
    Serial.println(" µs");
  }

  delay(100); // Small delay to avoid overwhelming the sensor
}
