#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to digital pin 7
#define ONE_WIRE_BUS 7

// Setup oneWire instance to communicate with any One-Wire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Print welcome message
  Serial.println("DS18B20 Temperature Sensor Example");
  Serial.println("==================================");
  
  // Start up the library
  sensors.begin();
}

void loop() {
  // Request temperature measurements
  sensors.requestTemperatures();
  
  // Read temperature from sensor (index 0 if only one sensor)
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Check if we got a valid reading
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print("°C, ");
  } else {
    Serial.println("Error: Could not read temperature data. Check sensor connection!");
  }
  
  // Wait before next reading (750ms for 12-bit resolution)
  delay(1000);
}
