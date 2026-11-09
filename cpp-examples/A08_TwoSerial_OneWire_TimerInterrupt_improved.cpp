#include <SoftwareSerial.h>
#include <TimerOne.h>
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

float temperatureC = DEVICE_DISCONNECTED_C;

int lastTime = 0;
const int hyppighet = 1000; //millisekunder mellom data utsending

const int OFFSET = 2000;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //Serial1.setTimeout(120); // 100 ms pakker

  // Starter biblioteket
  sensors.begin();
  sensors.requestTemperatures();
  // Set up timer interrupt hver 1 s
  Timer1.initialize(1000000); // 1 s
  Timer1.attachInterrupt(timerISR);
}

void timerISR() {
    sensors.requestTemperatures();
}

void loop() {
  data = Serial1.parseInt();
  temperatureC = sensors.getTempCByIndex(0); //Read temperature after last request

  if (millis() > (lastTime + hyppighet)) {
    lastTime = millis();

    data = data - OFFSET;
    if (abs(data) < 1024) { //Gyldig verdi
      Serial.print("Analog data: ");
      Serial.println(data);
    }
    if (temperatureC != DEVICE_DISCONNECTED_C) {  // Gyldig verdi != -127.00°C
      Serial.print("Temperature: ");
      Serial.print(temperatureC);
      Serial.println("°C");
    }
  }
}
