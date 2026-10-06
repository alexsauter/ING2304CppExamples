// === TIMING COMMANDS ===
unsigned long time = millis();    // Returns elapsed milliseconds since Arduino started running
                                    // Useful for non-blocking timing: if(millis() - startTime > delayTime) {}
                                    
unsigned long time = micros();    // Returns elapsed microseconds since Arduino started running  
                                    // More precise than millis(), good for measuring short events

// === PULSE MEASUREMENT (BLOCKING & NON-BLOCKING) ===
unsigned long duration = pulseIn(pin, value);              // Wait for pin to reach 'value', measure how long it stays there
unsigned long duration = pulseIn(pin, value, timeout);     // Same but with timeout in microseconds (prevents infinite waiting)

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);  // Initialize NewPing library with pins and max range, krever #include <NewPing.h> og installasjon av tilhørende bibliotek
unsigned int duration = sonar.ping();   // Returns echo time in microseconds (see: https://github.com/livetronic/Arduino-NewPing)
                                        // Returns NO_ECHO if no object detected within range
                                        // Use sonar.ping_cm() for direct distance measurement
                                        // Use sonar.ping_median(iterations) for reducing measurement errors

// === EXTERNAL INTERRUPT ===
volatile bool state;  //Variables changed during interrupt have to be of type volatile!

void setup() {
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), changeState, CHANGE);  // Start interrupt routine based on pin ECHO_PIN changing -> run function changeState
                                                                          // Mode: LOW, CHANGE, RISING, FALLING
                                                                          // See also: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
}

void loop() {
  if (state) {
    //do something
  }
}

//Interrupt Service Routine (ISR) triggered by CHANGE of ECHO_PIN
//Keep as short as possible!
void changeState() {
  state = !state;
}
