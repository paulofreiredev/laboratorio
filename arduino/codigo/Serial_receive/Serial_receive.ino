void setup() {
  Serial.begin(9600);
  Serial.print("entrada no arduino:");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);
  }
}
