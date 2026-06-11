#include <Servo.h>

#define TRIGGER_PIN 10
#define ECHO_PIN 11
#define SONAR_BASE_PIN 12

long duration;
long distance;
Servo sonarBase;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  sonarBase.attach(SONAR_BASE_PIN);
}

void loop() {
  for(int i=15;i<= 165; i++){
    interate(i);
  }
  for(int i=165; i>= 15; i--){
    interate(i);
  }
}

void interate(int i){
  sonarBase.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.println();  
}

int calculateDistance() {

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return 400;

  return duration * 0.034 / 2;
}
