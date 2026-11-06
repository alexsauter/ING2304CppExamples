#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Start en sekundær seriell port
SoftwareSerial Serial1(2, 3); // RX, TX

int data;

// Data ledning er koblet til digital pin 7
#define ONE_WIRE_BUS 7

// Setup oneWire instance for kommunikasjon med One-Wire enhet -> DS18B20 temp sensor
OneWire oneWire(ONE_WIRE_BUS);
// Bruk Dallas Temperature sensor bibliotek til tolkning av temperaturmålingen
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  // Starter biblioteket
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();  // Start fresh conversion each time
  delay(750);                     // Wait for conversion (required!)
  
  float temperatureC = sensors.getTempCByIndex(0);
  if (temperatureC == DEVICE_DISCONNECTED_C) {  // = -127.00°C
    Serial.println("ERROR: Sensor not connected or not responding!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println("°C");
  }
  
  //Eventuelt les (og fjern) alle verdiene som har ansamlet seg
  while (Serial1.available() > 0) {
    data = Serial1.parseInt(); //Leser bit-sekvens som int, overskriver eldre data med nyere
    Serial.println(data);      //Skriver ut til hoved seriell-port til debugging
  }
  delay(1000);  //Lengre pauser i avlesningen som her bør håndteres med while-løsningen over, ellers er if-løsningen godt nok
}
