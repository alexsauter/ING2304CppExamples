/* Servo styring og RC-mottakter avlesning */
#include <Servo.h>

#define RC_PIN 3 //Lese av PWM-signal fra RC-controller
#define Servo_PIN 11

Servo myservo;  // create servo object to control a servo

int val = 0;

//Slå av og på om puls-bredden til PWM skal skrives ut på seriell port
bool debug = false;

volatile unsigned long startTime = 0;
volatile int RC_duration = 0;

int old_val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RC_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RC_PIN), updateRC, CHANGE);

  myservo.attach(Servo_PIN);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (debug && (RC_duration > 0)) {
    Serial.print("Duration: ");
    Serial.print(RC_duration);
    Serial.println(" µs");
    delay(1000);
  } 
  val = map(RC_duration, 1000, 2000, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  //Redusere støy ved å bare endre på servoen når endrinen er mer enn 1 grad
  if (abs(old_val - val) > 1) {
      old_val = val;
      myservo.write(val);                  // sets the servo position according to the scaled value
  }
}

void updateRC() {
  bool activePuls = PIND & (1 << RC_PIN); //Read pin 3 (quickly)
                              
  if (activePuls && (startTime == 0)) //Starting puls and not startTime taken yet
  {
    startTime = micros(); //Take time at start of puls
  } else if (!activePuls && (startTime != 0)) { //After puls and startTime is taken
    RC_duration = micros() - startTime;
    startTime = 0;  //Empty startTime after use to prevent error condition
  } else {  //Error condition, should not happen - but if the case, reset to known condition
    RC_duration = startTime = 0;
  }
}
