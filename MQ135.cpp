#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ledPin = 6;

const int smokeDetectorPin = 1; // Analog pin for MQ135 sensor
const int smokeDetectorThreshold = 1000; // Adjust accordingly
LiquidCrystal_I2C lcd(0x27, 16, 2); // Address of your LCD module

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Wire.begin(8, 9); // Adjust SDA and SCL pins as per your ESP32 variant
  lcd.begin(16, 2); // Adjust the columns and rows of your LCD if necessary
  lcd.backlight();
}

void loop() {
  int smokeLevel = analogRead(smokeDetectorPin); // Read analog value from MQ135 sensor
  Serial.print("CO2 Level: ");
  Serial.println(smokeLevel);
  
  // Display smoke level on LCD
  lcd.setCursor(0, 0);
  lcd.print("CO2 Level: ");
  lcd.print(smokeLevel);
  lcd.print("    "); // Clear any leftover characters

  if (smokeLevel > smokeDetectorThreshold) {
    digitalWrite(ledPin, HIGH); // Turn on LED if smoke level exceeds threshold
    lcd.setCursor(0, 1);
    lcd.print("Smoke Detected");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED if smoke level is below threshold
    lcd.setCursor(0, 1);
    lcd.print("No Smoke     ");
  }

  delay(1000); // Adjust delay as needed
}
