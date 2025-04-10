# Automated Car Parking System

This project implements an automated car parking system using Arduino and a web application. The system utilizes various components to manage parking slots, allowing users to book and check availability through a web interface.

## Components

- **Arduino Uno**: The main controller for the parking system.
- **ESP32**: Used for Wi-Fi connectivity to communicate with the web application.
- **Servo Motor**: Controls the parking mechanism.
- **I2C LCD**: Displays information about parking slots and system status.
- **Keypad**: Allows user input for booking and managing parking slots.
- **IR Sensors**: Detects the presence of cars in parking slots.
- **LEDs**: Indicate the status of parking slots (available/occupied).
- **Paynow API**: Facilitates payment processing for booking parking slots.

## Features

- Live updates of parking slot availability.
- User login system for booking parking slots.
- Real-time communication between the Arduino and the web application.
- User-friendly interface for managing parking bookings.

## Setup Instructions

1. **Arduino Setup**:
   - Install the necessary libraries for LCD, Keypad, Servo, and IR Sensors.
   - Upload the `automated_parking.ino` sketch to the Arduino Uno.

2. **Web Application Setup**:
   - Navigate to the `WebApp` directory.
   - Run `npm install` to install the required dependencies.
   - Start the server using `node server/app.js`.

3. **Accessing the Web Application**:
   - Open a web browser and go to `http://localhost:3000` to access the application.

## Usage

- Users can log in to the web application to view available parking slots.
- Users can book a parking slot, which will update the system in real-time.
- The I2C LCD will display the current status of the parking system.

## Documentation

For detailed system design and architecture, refer to the `docs/system_design.md` file.