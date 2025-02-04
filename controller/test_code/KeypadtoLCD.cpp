#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>

// Define the keypad layout
const byte ROWS = 4; // Number of rows
const byte COLS = 3; // Number of columns

// Define the keys on the keypad
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Define the pins connected to the rows and columns of the keypad
byte rowPins[ROWS] = {4, 5, 6, 7}; 
byte colPins[COLS] = {8, 10, 9}; 

// Initialize the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Initialize the servo motor
Servo servo;

// Define the length of the master and attempt keys
const int len_key = 4;
// Define the master key
char master_key[len_key] = {'1','2','3','4'};
// Define the attempted key
char attempt_key[len_key];
int z=0;

// Setup function
void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  // Initialize I2C communication for LCD
  Wire.begin(19,18);
  // Initialize LCD
  lcd.init();
  // Turn on the backlight of LCD
  lcd.backlight();
  // Set the cursor to the first row of the LCD
  lcd.setCursor(0,0);
  // Display message on LCD
  lcd.print("Insert Password");
  // Attach the servo motor to pin 3
  servo.attach(3); 
}

// Function declaration
void checkKEY(); 

// Loop function
void loop() {
  // Get the pressed key from the keypad
  char key = keypad.getKey();
  // Set cursor position on LCD and display asterisk for each key pressed
  lcd.setCursor(z-1,1);
  lcd.print("*");
  // Check if a key is pressed
  if (key){
    // Check which key is pressed
    switch(key){
      // Clear the attempted key if '*' is pressed
      case '*':
        z=0;
        break;
      // Check the attempted key if '#' is pressed
      case '#':
        delay(100); // Added debounce
        checkKEY();
        break;
      // Store the pressed key in the attempted key array
      default:
         attempt_key[z]=key;
         z++;
    }
  }
}

// Function to check the attempted key
void checkKEY() {
  // Variable to count the number of correct key presses
  int correct=0;
  int i;
  // Iterate through the key arrays to check for correctness
  for (i=0; i<len_key; i++) {
    if (attempt_key[i]==master_key[i]) {
      correct++;
    }
  }
  // Check if all keys are correct and if the correct number of keys are entered
  if (correct==len_key && z==len_key) {
    // Display message on LCD
    lcd.setCursor(0,1);
    lcd.print("Correct Key");
    delay(3000);
    z=0;
    // Clear the LCD display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert Password");
    
    // Turn the servo to 180 degrees
    servo.write(180);
    delay(2000); // Wait for 2 seconds

    // Introduce a 5-second delay
    delay(5000);

    // Turn the servo back to 0 degrees
    servo.write(0);
    delay(2000); // Wait for 2 seconds
  } else {
    // Display message on LCD
    lcd.setCursor(0,1);
    lcd.print("Incorrect Key");
    delay(3000);
    z=0;
    // Clear the LCD display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert Password");
  }
  // Clear the attempted key array
  for (int zz=0; zz<len_key; zz++) {
    attempt_key[zz]=0;
  }
}

