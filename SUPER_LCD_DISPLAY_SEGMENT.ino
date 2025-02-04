#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>

// Pin Definitions
#define SHPin 32          // Soil Humidity Sensor Pin
#define WLPin 33          // Water Level Sensor Pin
#define RelayPin 25       // Relay Control Pin
#define DHT11PIN 17       // DHT11 Sensor Pin
#define MotorPin1 19      // Motor Pin 1
#define MotorPin2 18      // Motor Pin 2

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Initialize DHT11 sensor
dht11 DHT11;

// Variables to store previous sensor readings
int prevSHVal = -1;
int prevWLVal = -1;
int prevTemp = -1;
int prevHumidity = -1;

void setup() {
  // Set pin modes
  pinMode(SHPin, INPUT);
  pinMode(WLPin, INPUT);
  pinMode(RelayPin, OUTPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Setup PWM for motor control
  ledcSetup(1, 1200, 8); 
  ledcAttachPin(MotorPin1, 1);  
  ledcSetup(3, 1200, 8); 
  ledcAttachPin(MotorPin2, 3);  
}

void loop() {
  // Read sensor values
  int shVal = analogRead(SHPin); // Soil Humidity
  int wlVal = analogRead(WLPin); // Water Level

  int temp;
  int humidity;
  
  int chk = DHT11.read(DHT11PIN);
  temp = DHT11.temperature;
  humidity = DHT11.humidity;

  // Display sensor readings on LCD
  lcd.setCursor(0, 0);
  if (prevSHVal != shVal) {
    lcd.print("SH:"); // Soil Humidity
    lcd.setCursor(3, 0);
    lcd.print(shVal);
    prevSHVal = shVal;
  }
  
  lcd.setCursor(9, 0);
  if (prevTemp != temp) {
    lcd.print("T:"); // Temperature
    lcd.setCursor(12, 0);
    lcd.print(temp);
    prevTemp = temp;
  }

  lcd.setCursor(0, 1);
  if (prevWLVal != wlVal) {
    lcd.print("WL:"); // Water Level
    lcd.setCursor(4, 1);
    lcd.print(wlVal);
    prevWLVal = wlVal;
  }

  lcd.setCursor(9, 1);
  if (prevHumidity != humidity) {
    lcd.print("H:"); // Humidity
    lcd.setCursor(12, 1);
    lcd.print(humidity);
    prevHumidity = humidity;
  }

  // Control actions based on sensor readings
  if (500 >= shVal && wlVal >= 1000) {
    // Activate the relay to water the plant
    digitalWrite(RelayPin, HIGH);
    delay(400);
    digitalWrite(RelayPin, LOW);
    delay(700);
  }

  // Control the motor based on temperature
  if (temp >= 25) {
    // If temperature is high, activate MotorPin1
    ledcWrite(1, 100);
    ledcWrite(3, 0);
  } else {
    // If temperature is normal, turn off the motor
    delay(3000);
    ledcWrite(1, 0);
    ledcWrite(3, 0);
    delay(200);
  }
}

// This code tracks dht11 data, turn on fan when it is too hot and show water and humidity in the garden. Will automatically turn on the water pump for garden. Details on how much water should be pumped will be considered later if we have time, but the idea is good I think