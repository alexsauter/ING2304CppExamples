class UltraSonicSensor {
private:
    volatile uint8_t* trigPort;
    volatile uint8_t* echoPinRegister; 
    uint8_t trigBit;
    uint8_t echoBit;
    enum State {IDLE, TRIGGERED, MEASURING} state = IDLE;
    unsigned long startTime = 0;
    
public:
    UltraSonicSensor(uint8_t trigPin, uint8_t echoPin) {
        // Setup using direct port manipulation (like your code)
        trigPort = portOutputRegister(digitalPinToPort(trigPin));
        *trigPort &= ~_BV(digitalPinToBitMask(trigPin));  // LOW initially
        
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }
    
    void update() {  // Call this repeatedly in main loop - NON-BLOCKING!
        switch(state) {
            case IDLE:
                *trigPort |= _BV(digitalPinToBitMask(trigPin));
                delayMicroseconds(10);  // Could be replaced with timer too
                *trigPort &= ~_BV(digitalPinToBitMask(trigPin));
                state = TRIGGERED;
                break;
                
            case TRIGGERED:
                if (digitalRead(echoPin) == HIGH) {  // Or use PINB for speed
                    startTime = micros();
                    state = MEASURING;
                }
                break;
                
            case MEASURING:
                if (digitalRead(echoPin) == LOW) {
                    duration = micros() - startTime;
                    state = IDLE;  // Ready for next measurement
                }
                break;
        }
    }
};

// Usage in main sketch:
UltraSonicSensor sensor(TRIG_PIN, ECHO_PIN);

void loop() {
  sensor.update();  // Non-blocking update - returns immediately!
  
  if (sensor.hasNewReading()) {
    Serial.println(sensor.getDistanceCM());
  }
  
  // ← Arduino can do OTHER tasks here while waiting for echo!
}
