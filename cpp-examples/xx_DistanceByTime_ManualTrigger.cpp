/* Simplest Ultrasonic Pulse Measurement */

#define ECHO_PIN 2

void setup() {

  Serial.begin(9600);

  pinMode(ECHO_PIN, INPUT);

}

void loop() {

    unsigned long duration = pulseIn(ECHO_PIN, HIGH);

    

    if (duration > 0) {

      float distance_cm = duration / 58.2;

      Serial.print("Duration: ");

      Serial.print(duration);

      Serial.println(" µs");

      Serial.print("Distance: ");

      Serial.print(distance_cm, 1);

      Serial.println(" cm");

    } 

    

}
