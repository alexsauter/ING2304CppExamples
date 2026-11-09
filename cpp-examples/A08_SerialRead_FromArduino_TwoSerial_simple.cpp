#include <SoftwareSerial.h>

//Start en sekundær seriell port - til Sender-Arduino
SoftwareSerial Serial1(2, 3); // RX, TX

int data;

void setup() {
  Serial.begin(9600);   //Start seriell til PC
  Serial1.begin(9600);  //Start seriell til Arduino
}

void loop() {
  //Les neste datapakke om tilgjengelig, én om gangen
  if (Serial1.available() > 0) {
    data = Serial1.parseInt();   //Leser bit-sekvens som int - datatypen til variabelen
    Serial.println(data);
  }
}
