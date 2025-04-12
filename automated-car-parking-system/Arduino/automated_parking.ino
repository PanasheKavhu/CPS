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
LiquidCrystal_I2C lcd(0x27, 16, 2);

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

// Parking state
bool isOccupied[4] = {false, false, false, false}; // IR sensor detection
bool isBooked[4] = {false, false, false, false};   // Booking state

void setup() {
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
  // Update parking slot status
  for (int i = 0; i < 4; i++) {
    if (digitalRead(irSensorPins[i]) == HIGH) {
      isOccupied[i] = true;
    } else {
      if (!isBooked[i]) {
        isOccupied[i] = false;
      }
    }
  }

  // Display slot status one at a time
  for (int i = 0; i < 4; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot ");
    lcd.print(i + 1);
    lcd.print(": ");
    if (isOccupied[i] || isBooked[i]) {
      lcd.print("Occupied");
    } else {
      lcd.print("Available");
    }
    delay(2000);
  }

  // Update LEDs
  if (allSlotsFull()) {
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
  } else {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
  }

  // Handle keypad input
  char key = keypad.getKey();
  if (key) {
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  if (key >= '1' && key <= '4') {
    int slotIndex = key - '1';
    if (!isOccupied[slotIndex] && !isBooked[slotIndex]) {
      isBooked[slotIndex] = true;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Slot ");
      lcd.print(slotIndex + 1);
      lcd.print(": Booked");

      parkingServo.write(90); // Open gate
      delay(3000);
      parkingServo.write(0); // Close gate
    } else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Slot ");
      lcd.print(slotIndex + 1);
      lcd.print(": Taken");
    }
    delay(2000);
    lcd.clear();
  }
}

bool allSlotsFull() {
  for (int i = 0; i < 4; i++) {
    if (!isOccupied[i] && !isBooked[i]) {
      return false;
    }
  }
  return true;
}
