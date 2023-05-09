#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

// Define pins for sensors and actuators
const int temperaturePin = A0;
const int humidityPin = A1;
const int soilMoisturePin = A2;
const int lightIntensityPin = A3;
const int waterPumpPin = 2;
const int lightBulbPin = 3;

// Define variables for sensor readings
int temperature = 0;
int humidity = 0;
int soilMoisture = 0;
int lightIntensity = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(lightBulbPin, OUTPUT);
}

void loop() {
  // Read sensor data
  temperature = analogRead(temperaturePin);
  humidity = analogRead(humidityPin);
  soilMoisture = analogRead(soilMoisturePin);
  lightIntensity = analogRead(lightIntensityPin);

  // Send sensor data to neural network
  mySerial.print(temperature);
  mySerial.print(",");
  mySerial.print(humidity);
  mySerial.print(",");
  mySerial.print(soilMoisture);
  mySerial.print(",");
  mySerial.println(lightIntensity);

  // Read predictions from neural network
  if (mySerial.available()) {
    String prediction = mySerial.readString();
    if (prediction == "water_on") {
      digitalWrite(waterPumpPin, HIGH);
    }
    else if (prediction == "water_off") {
      digitalWrite(waterPumpPin, LOW);
    }
    else if (prediction == "light_on") {
      digitalWrite(lightBulbPin, HIGH);
    }
    else if (prediction == "light_off") {
      digitalWrite(lightBulbPin, LOW);
    }
  }

  // Wait for a short period before taking the next reading
  delay(5000);
}
