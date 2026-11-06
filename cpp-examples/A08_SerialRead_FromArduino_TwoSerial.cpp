#include <SoftwareSerial.h>

//Start en sekundær seriell port
SoftwareSerial Serial1(2, 3); // RX, TX

int data;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  /*
  //Les neste datapakke, én om gangen
  if (Serial1.available() > 0) {
    //a = Serial.read();     //Leser bit-sekvens som ASCII, men tolkes som int
    data = Serial1.parseInt(); //Leser bit-sekvens som int
    Serial.println(data);
  }
  */

  //Eventuelt les (og fjern) alle verdiene som har ansamlet seg
  while (Serial1.available() > 0) {
    data = Serial1.parseInt(); //Leser bit-sekvens som int, overskriver eldre data med nyere
    Serial.println(data);      //Skriver ut til hoved seriell-port til debugging
  }
  delay(1000);  //Lengre pauser i avlesningen som her bør håndteres med while-løsningen over, ellers er if-løsningen godt nok
}
