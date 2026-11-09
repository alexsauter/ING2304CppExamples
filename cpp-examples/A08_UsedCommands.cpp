// === UART/USB SERIAL COMMUNICATION ===
Serial.begin(9600);                     // Initialize serial at 9600 baud rate
Serial.available() > 0                  // Check if data is available to read
a = Serial.read();                      // Read byte as ASCII (returns int)
a = Serial.parseInt();                  // Parse incoming bytes as integer value
Serial.println(a);                      // Print integer converted to string representation
Serial.print("Temperature: ");          // Print without newline

// === SOFTWARE SERIAL (SECONDARY UART) ===
#include <SoftwareSerial.h>             // Required library for software-based serial
SoftwareSerial Serial1(RX_pin, TX_pin); // Create secondary serial object (RX, TX pins)
Serial1.begin(9600);                    // Initialize software serial at specified baud rate
Serial1.available() > 0                 // Check if data available on secondary port
data = Serial1.parseInt();              // Parse incoming data as integer from secondary port

// === I2C COMMUNICATION ===
#include <Wire.h>                        // Required library for I2C communication

// MASTER MODE:
Wire.begin();                            // Join I2C bus as master (no address needed)
Wire.requestFrom(address, bytes);        // Request specific number of bytes from slave device
Wire.available() > 0                     // Check if data is available to read
c = Wire.read();                         // Read received byte

// SLAVE MODE:
Wire.begin(address);                      // Join I2C bus with specific address (e.g., #8)
Wire.onRequest(handler_function);         // Register function to call when master requests data
Wire.write(value);                        // Send data back to master during request event

// === ONEWIRE PROTOCOL ===
#include <OneWire.h>                      // Required library for OneWire communication
#define ONE_WIRE_BUS pin_number           // Define which digital pin connects to sensor
OneWire oneWire(ONE_WIRE_BUS);            // Create OneWire instance on specified pin

// For DS18B20 Temperature Sensor:
#include <DallasTemperature.h>            // Required library for DS18B20 sensors
DallasTemperature sensors(&oneWire_instance)  // Pass OneWire reference to temperature lib
sensors.begin();                          // Initialize DallasTemperature library
sensors.requestTemperatures();            // Send command to get temperatures from all sensors
float temp = sensors.getTempCByIndex(0);  // Get temperature in Celsius by sensor index (0-based)
DEVICE_DISCONNECTED_C                     // Constant returned if sensor disconnected (-127°C)
