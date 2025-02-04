#define ButtonPin     5   // Define a button pin
#define PhotocecllPin 34  // Define the photoresistor pin
#define LED           27  // Define LED pin

int value = 0;  // Define a value to detect button status

void setup() {
  // Initialize serial port and set baud rate to 9600
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(ButtonPin, INPUT);
  pinMode(PhotocecllPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Read the value of the photoresistor
  int photoValue = analogRead(PhotocecllPin);
  
  // Print the photoresistor value
  Serial.print("Photocecll value: ");
  Serial.println(photoValue);
  
  // Determine LED state based on photoresistor value
  if (photoValue >= 1000) {
    // LED turns off when it's bright
    digitalWrite(LED, LOW);
    Serial.println("LED OFF");
  } else {
    // LED turns on when it's dark
    digitalWrite(LED, HIGH);
    Serial.println("LED ON");
  }
  
  // Check if the button is pressed
  int buttonState = digitalRead(ButtonPin);
  if (buttonState == LOW) {
    // If the button is pressed, keep the LED on
    digitalWrite(LED, HIGH);
  }
  
  delay(100);
}

//Turn button on => LED on. If dark => LED on and pushing button would not affect the system