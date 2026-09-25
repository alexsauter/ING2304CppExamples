#include <NewPing.h>
#define TRIG_PIN 9      // HC-SR04 Trig pin connected to Arduino digital pin 9
#define ECHO_PIN 10     // HC-SR04 Echo pin connected to Arduino digital pin 10
#define MAX_DISTANCE 400  // Maximum sensing distance in centimeters (affects timeout)

NewSonar sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);  // Initialize NewPing library with pins and max range

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50); // Recovery time between pings
  
  // Get raw timing once (this performs the actual measurement)
  unsigned int duration = sonar.ping(); // Returns NO_ECHO if no object detected within range
                                        //Use sonar.ping_cm() for direct distance measurement
  
  if (duration != NO_ECHO) {  // Valid echo received - convert timing to distance
    Serial.print("Raw time: ");
    Serial.print(duration);
    Serial.println(" µs");
    
    // Convert timing to distance manually for educational purposes
    float distance_cm = duration / 58.2;  // Speed of sound conversion formula (same as with pulsIn-function)
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
  } else {
    Serial.println("Timeout - no object detected within range");
  }

  delay(100);
}
