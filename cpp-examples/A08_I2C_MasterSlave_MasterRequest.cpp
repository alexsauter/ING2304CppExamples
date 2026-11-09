#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 1);    // request 1 byte from peripheral device #8

  if (Wire.available()) {    // peripheral may send less than requested
    int c = Wire.read();     // receive a byte as a number 0..255
    Serial.println(c);       // print the number for debugging
  }

  delay(500);
}
