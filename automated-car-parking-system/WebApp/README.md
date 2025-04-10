# Automated Car Parking System

## Overview
The Automated Car Parking System is a project designed to provide an efficient and user-friendly solution for parking management. It utilizes an Arduino Uno and an ESP32 to control the parking slots, monitor availability using IR sensors, and provide a web interface for users to book parking slots.

## Components
- **Arduino Uno**: Main controller for managing hardware components.
- **ESP32**: Handles communication between the Arduino and the web application.
- **Servo Motor**: Controls the parking mechanism.
- **I2C LCD**: Displays information about parking slot availability.
- **Keypad**: Allows users to input commands for booking and managing parking.
- **IR Sensors**: Detects the presence of vehicles in parking slots.
- **LEDs**: Indicate the status of parking slots (available/occupied).
- **Paynow API**: Facilitates payment processing for parking bookings.

## Web Application
The web application provides a user interface for:
- User login
- Booking parking slots
- Viewing live updates of parking slot availability

### Setup Instructions
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/automated-car-parking-system.git
   ```
2. Navigate to the WebApp directory:
   ```
   cd automated-car-parking-system/WebApp
   ```
3. Install the required dependencies:
   ```
   npm install
   ```
4. Start the server:
   ```
   npm start
   ```
5. Access the web application at `http://localhost:3000`.

## Usage
- Users can log in to the web application using their credentials.
- Once logged in, users can view available parking slots and book a slot.
- The system updates the parking slot availability in real-time.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.