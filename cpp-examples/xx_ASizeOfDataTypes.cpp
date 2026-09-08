void setup() {
  Serial.begin(9600);
  
  // Wait for serial monitor to open (optional)
  //while (!Serial);
  
 }

void loop() {
 Serial.println("Data Type Sizes:");
  Serial.println("A byte is " + String(8) + " bits");  // CHAR_BIT equivalent on AVR
  Serial.println();
  
  // Note: Arduino doesn't have std::setw, so we'll format manually
  Serial.println("Type            Size (bytes)");
  Serial.println("------------------------------");
  printSize("bool", sizeof(bool));
  printSize("char", sizeof(char));
  printSize("short", sizeof(short));
  printSize("int", sizeof(int));
  printSize("long", sizeof(long));
  printSize("long long", sizeof(long long));
  printSize("float", sizeof(float));
  printSize("double", sizeof(double));
  printSize("long double", sizeof(long double));
  delay(10000);
}

void printSize(String typeName, int size) {
  int padding = 16 - typeName.length()-2;
  Serial.print(typeName + ": ");
  for (int i = 0; i < padding; i++) {
    Serial.print(" ");
  }
  Serial.println(String(size) + " bytes");
}
