# Automated Car Parking System Design Documentation

## Introduction
This document outlines the system design for the Automated Car Parking System, detailing the architecture, components, and interactions within the system.

## System Architecture
The system is composed of two main components: the Arduino-based hardware system and the web application. The Arduino system manages the physical aspects of parking, while the web application provides a user interface for booking and managing parking slots.

### Hardware Components
1. **Arduino Uno**: The main microcontroller that controls the parking system.
2. **ESP32**: Used for Wi-Fi connectivity to communicate with the web application.
3. **Servo Motor**: Controls the parking barrier for entry and exit.
4. **I2C LCD**: Displays the status of parking slots and system messages.
5. **Keypad**: Allows users to input commands and access the system.
6. **IR Sensors**: Detects the presence of vehicles in parking slots.
7. **LEDs**: Indicate the status of parking slots (available/occupied).

### Software Components
1. **Arduino Sketch (automated_parking.ino)**: The main program that initializes components, reads sensor data, controls the servo motor, and updates the LCD.
2. **Web Application**: A Node.js application that provides a user interface for booking and managing parking slots.
   - **Frontend**: HTML, CSS, and JavaScript files for user interaction.
   - **Backend**: Express.js server handling API requests for user login, booking, and live updates.

## Component Interactions
- The Arduino system continuously monitors the parking slots using IR sensors. When a vehicle is detected, the system updates the status of the corresponding slot.
- Users can log in to the web application, view available parking slots, and make bookings.
- The web application communicates with the Arduino system via the ESP32 to retrieve live updates on parking slot availability.
- Upon booking a slot, the web application sends a command to the Arduino to activate the servo motor, allowing the vehicle to enter.

## Database Design
The web application uses a database to store user information and parking slot availability. The database schema includes:
- **Users**: Stores user credentials and booking history.
- **Parking Slots**: Stores information about each parking slot, including its status (available/occupied).

## Conclusion
This system design provides a comprehensive overview of the Automated Car Parking System, detailing the interactions between hardware and software components. The design aims to create an efficient and user-friendly parking management solution.