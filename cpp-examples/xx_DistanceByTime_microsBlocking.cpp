#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Ensure trigger starts LOW
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  unsigned long duration;
  
  // Step 1: Send 10µs HIGH pulse to trigger measurement
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);           // Critical timing - must be at least 10µs
  digitalWrite(TRIG_PIN, LOW);

  // Step 2: Measure how long Echo pin stays HIGH using micros()
  // Wait for echo to go HIGH (start of measurement)
  while (digitalRead(ECHO_PIN) == LOW);  // Blocking wait - could hang!
  
  unsigned long startTime = micros();    // Record start time
  
  // Wait for echo to go LOW again (end of measurement)
  while (digitalRead(ECHO_PIN) == HIGH); // Another blocking point!

  duration = micros() - startTime;      // Calculate pulse width in microseconds

  // Step 3: Convert timing to distance
  float distance_cm = duration / 58.2;    // Speed of sound conversion
  
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" µs");
  
  Serial.print("Distance: ");
  Serial.print(distance_cm, 1);  // One decimal place for precision
  Serial.println(" cm");

  delay(200);  // Wait before next measurement
}
