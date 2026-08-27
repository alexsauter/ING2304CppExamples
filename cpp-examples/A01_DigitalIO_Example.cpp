// Pin definitions
const int BUTTON_PIN = 2;    // Button connected to digital pin 2
const int LED_PIN = 13;      // Built-in LED for testing

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configure button with internal pull-up
  pinMode(LED_PIN, OUTPUT);           // Configure LED as output
  Serial.begin(9600);                 // Start serial communication for debugging
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // Read button state
  
  if (buttonState == LOW) {        // Button pressed (active-low with INPUT_PULLUP)
    digitalWrite(LED_PIN, HIGH);   // Turn on LED
    Serial.println("Button PRESSED");
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn off LED
    Serial.println("Button RELEASED");
  }
  
  delay(100);                      // Small delay for stability
}
