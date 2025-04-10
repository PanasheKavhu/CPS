1|# Automated Car Parking System
2|
3|## Implementation Guide
4|
5|### Prerequisites
6|- Arduino IDE 1.8.x or newer
7|- Node.js 14.x or newer
8|- MongoDB 4.4 or newer
9|- Required hardware components:
10|  - Arduino Uno + ESP32
11|  - Servo motor (SG90)
12|  - I2C LCD 16x2
13|  - IR sensors (4x)
14|  - LEDs (Red/Green)
15|  - 4x4 membrane keypad
16|
17|### Hardware Setup
18|1. Connect components according to this schematic:
19|   ```
20|   Arduino Uno Pin -> Component
21|   ----------------------------
22|   Digital 2-5     -> IR Sensors (Slot 1-4)
23|   Digital 6       -> Servo Motor
24|   Digital 7       -> Green LED
25|   Digital 8       -> Red LED
26|   A4-A5           -> I2C LCD
27|   Digital 9-12    -> Keypad Rows
28|   Analog 0-2      -> Keypad Columns
29|   ```
30|
31|2. Connect ESP32 to Arduino via serial pins (TX/RX)
32|
33|### Software Installation
34|1. Clone the repository:
35|   ```bash
36|   git clone https://github.com/yourusername/automated-car-parking-system.git
37|   cd automated-car-parking-system
38|   ```
39|
40|2. Arduino Setup:
41|   - Install required libraries:
42|     - LiquidCrystal_I2C
43|     - Keypad
44|     - Servo
45|     - ArduinoJSON
46|   - Upload sketches:
47|     1. Open `Arduino/automated_parking.ino`
48|     2. Upload to Arduino Uno
49|     3. Open `Arduino/esp32_parking.ino`
50|     4. Update WiFi credentials (line 6-7)
51|     5. Upload to ESP32
52|
53|3. Web Application Setup:
54|   ```bash
55|   cd WebApp
56|   npm install
57|   ```
58|
59|4. Configure environment:
60|   - Create `.env` file in `WebApp` directory:
61|     ```env
62|     MONGODB_URI=mongodb://localhost:27017/parkingSystem
63|     PORT=3000
64|     ```
65|
66|### Running the System
67|1. Start MongoDB service
68|2. Run the web server:
69|   ```bash
70|   cd WebApp
71|   npm start
72|   ```
73|3. Power on Arduino system
74|4. Access web interface at `http://localhost:3000`
75|
76|### Key Features
77|- Real-time parking slot monitoring via IR sensors
78|- Web-based booking system with user authentication
79|- Automatic barrier control using servo motor
80|- Visual status indicators (LCD + LEDs)
81|
82|### Dependencies
83|**Arduino Libraries**
84|- LiquidCrystal_I2C v1.1.2
85|- Keypad v3.1.1
86|- Servo v1.1.8
87|
88|**Node.js Packages**
89|- Express 4.17.x
90|- Mongoose 5.10.x
91|- CORS 2.8.x
92|
93|## Troubleshooting
94|- Ensure serial connection between Arduino/ESP32
95|- Verify WiFi credentials in `esp32_parking.ino`
96|- Check MongoDB service is running
97|- Confirm all sensor connections are secure 