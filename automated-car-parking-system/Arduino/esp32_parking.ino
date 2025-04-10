#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "Chels";
const char* password = "panashee";

// Server URL
const char* serverUrl = "http://< 172.16.33.156>:3000/api/slots";

// Parking slot status
bool parkingSlots[4] = {false, false, false, false}; // false = empty, true = occupied

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Simulate parking slot updates (replace with actual sensor data)
  for (int i = 0; i < 4; i++) {
    parkingSlots[i] = digitalRead(i + 2); // Replace with actual sensor pins
  }

  // Send parking slot updates to the server
  sendParkingSlotUpdates();

  // Check for booking commands from the server
  checkForBookings();

  delay(5000); // Adjust as needed
}

void sendParkingSlotUpdates() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    StaticJsonDocument<200> jsonDoc;
    JsonArray slots = jsonDoc.createNestedArray("slots");
    for (int i = 0; i < 4; i++) {
      slots.add(parkingSlots[i]);
    }

    String payload;
    serializeJson(jsonDoc, payload);

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.println("Parking slot updates sent successfully");
    } else {
      Serial.println("Error sending parking slot updates");
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

void checkForBookings() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String response = http.getString();
      StaticJsonDocument<200> jsonDoc;
      deserializeJson(jsonDoc, response);

      // Process booking commands (example: open slot for a specific ID)
      if (jsonDoc.containsKey("bookedSlot")) {
        int bookedSlot = jsonDoc["bookedSlot"];
        Serial.print("Slot booked: ");
        Serial.println(bookedSlot);
        // Add logic to open the slot (e.g., move servo)
      }
    } else {
      Serial.println("Error checking for bookings");
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}