const int irSensorPin = A1;  // Replace with the actual pin where the IR sensor is connected
const int buzzerPin = 13;    // Replace with the actual pin where the buzzer is connected

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int irSensorValue = digitalRead(irSensorPin);

  if (irSensorValue == HIGH) {
    // Object detected, turn on the buzzer
    digitalWrite(buzzerPin, LOW);
  } else {
    // No object detected, turn off the buzzer
    digitalWrite(buzzerPin, HIGH);
  }

  delay(100);  // Add a small delay to avoid rapid toggling due to noise or bouncing
}
