#include <DHT.h>

// DHT sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Gas sensor and buzzer configuration
const int gasSensorPin = A0;
const int gasBuzzerPin = 13;

// IR sensor and buzzer configuration
const int irSensorPin = A1;
const int irBuzzerPin = 13;

// Ultrasonic sensor and LED configuration
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int objectLedPin = 3;
const int DISTANCE_THRESHOLD = 40;

void setup() {
  // DHT sensor setup
  Serial.begin(9600);
  Serial.println("Sensor and Buzzer Test!");

  dht.begin();

  // Gas sensor and buzzer setup
  pinMode(gasSensorPin, INPUT);
  pinMode(gasBuzzerPin, OUTPUT);

  // IR sensor and buzzer setup
  pinMode(irSensorPin, INPUT);
  pinMode(irBuzzerPin, OUTPUT);

  // Ultrasonic sensor and LED setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(objectLedPin, OUTPUT);
}

void loop() {
  // DHT sensor readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print("DHT Sensor - Humidity: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.println(temperature);
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Gas sensor and buzzer
  int gasValue = analogRead(gasSensorPin);
  int gasThreshold = 500;

  if (gasValue > gasThreshold) {
    Serial.println("Gas detected! Activating gas buzzer...");
    activateBuzzer(gasBuzzerPin);
  } else {
    Serial.println("No gas detected.");
    deactivateBuzzer(gasBuzzerPin);
  }

  // IR sensor and buzzer
  int irSensorValue = digitalRead(irSensorPin);

  if (irSensorValue == HIGH) {
    Serial.println("Object detected! Activating IR buzzer...");
    deactivateBuzzer(irBuzzerPin);
  } else {
    Serial.println("No object detected.");
    activateBuzzer(irBuzzerPin);
  }

  // Ultrasonic sensor and LED
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration_us = pulseIn(ECHO_PIN, HIGH);
  float distance_cm = 0.017 * duration_us;

  if (distance_cm < DISTANCE_THRESHOLD) {
    Serial.println("Object within range! Turning on LED...");
    digitalWrite(objectLedPin, HIGH);
  } else {
    Serial.println("Object out of range.");
    digitalWrite(objectLedPin, LOW);
  }

  Serial.print("Ultrasonic Sensor - Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(2000); // Adjust the delay based on your application and sensor response time
}

void activateBuzzer(int pin) {
  digitalWrite(pin, HIGH);
}

void deactivateBuzzer(int pin) {
  digitalWrite(pin, LOW);
}
