#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// Pin definitions
const int irSensorPins[] = {2, 3, 4, 5}; // IR sensor pins for 4 parking slots
const int servoPin = 6; // Servo motor pin
const int ledGreenPin = 7; // Green LED pin
const int ledRedPin = 8; // Red LED pin

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address as needed

// Keypad setup
const byte rows = 4; 
const byte cols = 4; 
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {9, 10, 11, 12}; 
byte colPins[cols] = {13, A0, A1, A2}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

// Servo setup
Servo parkingServo;

// Parking slot status
bool parkingSlots[4] = {false, false, false, false}; // false = empty, true = occupied

void setup() {
  // Initialize components
  lcd.begin();
  parkingServo.attach(servoPin);
  
  for (int i = 0; i < 4; i++) {
    pinMode(irSensorPins[i], INPUT);
  }
  
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Check parking slots
  for (int i = 0; i < 4; i++) {
    if (digitalRead(irSensorPins[i]) == HIGH) {
      parkingSlots[i] = true; // Car detected
      digitalWrite(ledRedPin, HIGH); // Indicate occupied slot
      lcd.setCursor(0, 0);
      lcd.print("Slot ");
      lcd.print(i + 1);
      lcd.print(": Occupied");
    } else {
      if (parkingSlots[i]) {
        parkingSlots[i] = false; // Car left
        digitalWrite(ledRedPin, LOW); // Indicate available slot
        lcd.setCursor(0, 0);
        lcd.print("Slot ");
        lcd.print(i + 1);
        lcd.print(": Available");
      }
    }
  }

  // Handle keypad input
  char key = keypad.getKey();
  if (key) {
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  // Implement booking logic based on key press
  // For example, if '1' is pressed, attempt to book slot 1
  if (key >= '1' && key <= '4') {
    int slotIndex = key - '1';
    if (!parkingSlots[slotIndex]) {
      parkingSlots[slotIndex] = true; // Book the slot
      parkingServo.write(90); // Move servo to park the car
      lcd.setCursor(0, 1);
      lcd.print("Slot ");
      lcd.print(slotIndex + 1);
      lcd.print(": Booked");
      digitalWrite(ledGreenPin, HIGH); // Indicate booked slot
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Slot ");
      lcd.print(slotIndex + 1);
      lcd.print(": Taken");
    }
  }
}