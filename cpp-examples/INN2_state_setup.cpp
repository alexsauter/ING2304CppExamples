//State variabel -> separate states chosen by user
volatile int state = 0;
const int state_max = 2;

void setup() {
  pinMode(2,INPUT);   // Use button at pin 2 to switch state
  attachInterrupt(digitalPinToInterrupt(2),iterateState,RISING); // External interrupt -> switch state immediately when button is pushed 

  Serial.begin(9600); // Debugging via Serial-monitor
}

void loop() {
  Serial.println(state);
  delay(1000);
}

void iterateState() {
  state = ++state % (state_max+1); // Increase state by 1, modulo state_max -> restart at state 0 when reaching max-state
}
