/* Ultrasonic Pulse Measurement with Interrupt */
#define ECHO_PIN 2

//All variables changed during an interrupt must be of type volatile!!
volatile bool activePuls = false;

volatile unsigned long startTime = 0;
volatile int duration = 0;    //If datatype int is chosen, all valid measurements are withing positive number range
                              //-> All invalid (out of range = ~47 000 µs timeout) result in negative numbers, filtered out with >0 condition

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT); //Use ECHO_PIN as input-pin
  //Start interrupt routine on pin ECHO_PIN (if valid interrupt pin)
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), takeTime, CHANGE);
}

void loop() {
  if (duration > 0) {  //Check if new valid measurement (over 0 if measured and within range)
    float distance_cm = duration / 58.2; //Convert to distance (via speed of sound)
    //Slower serial write should be outside of ISR, like here:
    Serial.print("Duration: ");
    Serial.print(duration);
    Serial.println(" µs");
    Serial.print("Distance: ");
    Serial.print(distance_cm, 1);
    Serial.println(" cm");
    duration = 0; //Marking end of current measurement: forget duration and wait for new measurement
  } else if (duration < 0) { //Invalid measurement, due to overflow negative!
    float distance_cm = duration / 58.2; //Konvertering til avstand (via speed of sound)
    Serial.print("Duration for out of reach: ");
    Serial.print(duration);
    Serial.println(" µs");
    duration = 0; //Marking end of current measurement: forget duration and wait for new measurement
  }
  //delay(10000); //Other code taking long time doesn't influence measurement
}

//Interrupt Service Routine (ISR) triggered by CHANGE of ECHO_PIN
//Keep as short as possible!
void takeTime() {
  //Read button to check if rising og falling edge
  activePuls = PIND & (1 << PD2); //Read pin 2 (quickly)
                              //After change, if HIGH -> Rising, if LOW -> Falling
                              
  if (activePuls && (startTime == 0)) //Starting puls and not startTime taken yet
  {
    //duration = 0; //Should be 0 by default at this stage
    startTime = micros(); //Take time at start of puls
  } else if (!activePuls && (startTime != 0)) { //After puls and startTime is taken
    duration = micros() - startTime;  //Calculate duration at end of puls using the starttime
    startTime = 0;  //Empty startTime after use to prevent error condition
  } else {  //Error condition, should not happen - but if the case, reset to known condition
    duration = startTime = 0;
  }
}
