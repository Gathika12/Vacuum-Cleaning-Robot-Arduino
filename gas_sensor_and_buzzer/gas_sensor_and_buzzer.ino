const int gasSensorPin = A0; // Analog pin for the gas sensor
const int buzzerPin = 13;    // Digital pin for the buzzer

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  
  // You may need to adjust the threshold based on your sensor and environment
  int threshold = 500;

  if (gasValue > threshold) {
    Serial.println("Gas detected! Activating buzzer...");
    activateBuzzer();
  } else {
    Serial.println("No gas detected.");
    deactivateBuzzer();
  }

  delay(1000); // Adjust the delay based on your application and sensor response time
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);
}

void deactivateBuzzer() {
  digitalWrite(buzzerPin, LOW);
}
