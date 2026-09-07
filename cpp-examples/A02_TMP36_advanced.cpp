// Define the analog pin connected to TMP36
#define TMP36_PIN A0

void setup() {
// Start serial communication at 9600 baud
Serial.begin(9600);
}

void loop() {
// Read the analog value from TMP36
int sensorValue = analogRead(TMP36_PIN);

// Convert the analog value to voltage (in millivolts)
float voltage = sensorValue * (5000.0 / 1024.0);

// Convert voltage to temperature in Celsius
float temperatureC = (voltage - 500) / 10;

// Print temperature in Celsius
Serial.print("Temperature: ");
Serial.print(temperatureC);
Serial.println(" °C");

delay(1000); // Wait for a second before the next reading
}
