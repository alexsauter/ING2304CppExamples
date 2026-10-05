/* Simple Ultrasonic Pulse Measurement with Manual Trigger */
#define ECHO_PIN 2

//All variables changed during an interrupt must be of type volatile!!
volatile bool lastButton = false;
volatile bool currButton = false;

volatile unsigned long startTime = 0;
volatile unsigned long stopTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), takeTime, CHANGE);  // Start interrupt routine based on pin ECHO_PIN changing -> run function takeTime
}

void loop() {
    //unsigned long duration = pulseIn(ECHO_PIN, HIGH); //Måler pulsbredden (blokkende)
    unsigned long duration = (stopTime - startTime);  //Determine duration, might be 0 or underflow if stop and start are out of sync

    if ((duration > 0) && (duration < 400*58.2)) {  //Check if new valid measurement (over 0 and within range)
      float distance_cm = duration / 58.2; //Konvertering til avstand (via speed of sound)
      //Slower serial write should be outside of ISR, like here:
      Serial.print("Duration: ");
      Serial.print(duration);
      Serial.println(" µs");
      Serial.print("Distance: ");
      Serial.print(distance_cm, 1);
      Serial.println(" cm");
      startTime = stopTime = 0; //Reset time-variables to be sure to not reuse them
    } 
}

//Interrupt Service Routine (ISR) triggered by CHANGE of ECHO_PIN
//Keep as short as possible!
void takeTime() {
  //Read button to check if rising og falling edge
  lastButton = currButton; //Remember last button before reading new state
  currButton = PIND & (1 << PD2); //Read pin 2

  if (currButton && !lastButton) //Rising edge condition
  {
    startTime = micros();
  }
  if (!currButton && lastButton) //Falling edge condition
  {
    stopTime = micros();
  }
}
