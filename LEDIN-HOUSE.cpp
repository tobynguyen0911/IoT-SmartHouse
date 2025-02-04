#include <Arduino.h>


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // LED
  pinMode(3, INPUT_PULLUP); // PIR sensor
}


void loop() {
  if (digitalRead(3) == LOW) { // If PIR sensor detects motion
    digitalWrite(2, HIGH); // Turn on LED
    Serial.println("Movement detected");
    delay(10000); // Delay for 1 second (adjust as needed)
  } else {
    digitalWrite(2, LOW); // Turn off LED if no motion detected
    Serial.println("No movement detected");
    delay(100); // Short delay to debounce the PIR sensor output
  }
}

// Build inside the house. We will use a different ESP32C3-M1 to mount this and the MQ135 smoke detector