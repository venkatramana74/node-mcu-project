#include <Keypad.h>
#include <Servo.h>

// Define the keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {31, 30, 29, 28}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {27, 26, 25, 24}; // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the servo motor
Servo lockServo;
const  char lockPin = A0;

// Define the password
char password[] = "1234";
char enteredPassword[5];
int passwordIndex = 0;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Attach the servo motor to the lock pin
  lockServo.attach(lockPin);

  // Reset the entered password
  resetPassword();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '#') {
      // Check if the entered password is correct
      if (strcmp(enteredPassword, password) == 0) {
        Serial.println("Access granted!");
        unlockDoor();
        delay(2000);
        lockDoor();
      } else {
        Serial.println("Access denied!");
        delay(2000);
      }
      resetPassword();
    } else if (key == '*') {
      resetPassword();
    } else {
      // Add the entered key to the password
      if (passwordIndex < 4) {
        enteredPassword[passwordIndex] = key;
        passwordIndex++;
      }
      Serial.print("*");
    }
  }
}

void resetPassword() {
  memset(enteredPassword, 0, sizeof(enteredPassword));
  passwordIndex = 0;
}

void unlockDoor() {
  lockServo.write(90); // Rotate the servo to unlock the door
}

void lockDoor() {
  lockServo.write(0); // Rotate the servo to lock the door
}