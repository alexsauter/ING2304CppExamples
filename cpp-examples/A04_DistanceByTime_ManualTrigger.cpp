/* Simple Ultrasonic Pulse Measurement with Manual Trigger */
#define ECHO_PIN 2

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
    unsigned long duration = pulseIn(ECHO_PIN, HIGH); //Måler pulsbredden (blokkende)

    if (duration > 0) {
      float distance_cm = duration / 58.2; //Konvertering til avstand (via speed of sound)

      Serial.print("Duration: ");
      Serial.print(duration);
      Serial.println(" µs");
      Serial.print("Distance: ");
      Serial.print(distance_cm, 1);
      Serial.println(" cm");
    } 
}
