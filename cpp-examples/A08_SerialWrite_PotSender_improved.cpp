//#include <SoftwareSerial.h>

//SoftwareSerial Serial1(0, 1); // RX, TX

const int OFFSET = 2000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0)+OFFSET);
  delay(100);
}
