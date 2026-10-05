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

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), takeTime, CHANGE);
}

void loop() {
    //unsigned long duration = pulseIn(ECHO_PIN, HIGH); //Måler pulsbredden (blokkende)
    unsigned long duration = (stopTime - startTime);

    if ((duration > 0) && (duration < 400*58.2)) {  //Maximal range is 400 cm
      float distance_cm = duration / 58.2; //Konvertering til avstand (via speed of sound)

      Serial.print("Duration: ");
      Serial.print(duration);
      Serial.println(" µs");
      Serial.print("Distance: ");
      Serial.print(distance_cm, 1);
      Serial.println(" cm");
      startTime = stopTime = 0;
    } 
}

//Interrupt Service Routine (ISR) triggered by CHANGE of ECHO_PIN
//Keep as short as possible!
void takeTime() {
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
