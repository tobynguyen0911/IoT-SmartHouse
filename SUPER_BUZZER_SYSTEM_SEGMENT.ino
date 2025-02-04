// Define pins for various components
#define SteamPin 35            // Steam sensor pin
#define BuzzerPin 16           // Buzzer pin
#define PyroelectricPIN 23     // PIR motion sensor pin

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(SteamPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(PyroelectricPIN, INPUT);
}

void loop() {
  // Read the value from the steam sensor
  int ReadValue = analogRead(SteamPin);
  Serial.print("Steam Value: ");
  Serial.println(ReadValue);
  
  // Read the value from the PIR motion sensor
  int pirValue = digitalRead(PyroelectricPIN);
  
  // If both motion and steam detected, play unique sound
  if (pirValue && ReadValue >= 800) {
    uniqueSound();
  }
  // If there is someone detected
  if (pirValue) {
    Serial.println("Someone");
    // alarm for pir sensor
    for(int i = 200; i <= 1000; i+= 10) {
      tone(BuzzerPin,i);
      delay(10);
    }
    for(int i = 1000; i>= 200; i-= 10) {
      tone(BuzzerPin,i);
      delay(10);
    }
  } 
  //Determine whether the detected value is within 800~2000
  if(ReadValue >= 800 && 2000 > ReadValue){
    //Execute for 3 times
    for (int i = 0; i < 3; i++) {
      tone(BuzzerPin,200);
      delay(100);
      noTone(BuzzerPin);
      delay(100);
    }
  }
  //Determine whether the detected value is within 2000~4000
  else if (ReadValue >= 2000 && 4000 >= ReadValue) {
    for (int i = 0; i < 3; i++) {
      tone(BuzzerPin,400);
      delay(100);
      noTone(BuzzerPin);
      delay(100);
    }
  }
  //Determine whether the detected value is greater than 4000
  else if (ReadValue > 4000) {
    for (int i = 0; i < 3; i++) {
      tone(BuzzerPin,600);
      delay(100);
      noTone(BuzzerPin);
      delay(100);
    }
  }
  noTone(BuzzerPin);
  delay(500);
}

// Function to trigger a unique sound when both motion and steam detected
// Execute for 3 times
void uniqueSound() {
  for (int i = 300; i <= 2000; i+=15) {
    tone(BuzzerPin, i);
    delay(10);
  }
}
