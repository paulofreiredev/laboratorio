
#define BUTTON  8

int counter = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("Listening button events at pin 8\n");
}

void loop() {
  int pressed = digitalRead(BUTTON);
  if(pressed == 0) {
    counter ++;
    Serial.print("The button was pressed ");
    Serial.print(counter);
    Serial.println(" times!!");
  }
  delay(200);
}
