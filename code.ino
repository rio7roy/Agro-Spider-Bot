#include <WiFi.h>               // Include WiFi library for ESP32 connectivity
#include <BlynkSimpleEsp32.h>   // Include Blynk library for IoT functionality

// Wi-Fi credentials
char ssid[] = "YourSSID";       // Replace with your Wi-Fi SSID
char pass[] = "YourPassword";   // Replace with your Wi-Fi password

// Blynk authentication token
char auth[] = "YourAuthToken";  // Replace with your Blynk Auth Token

// Motor and sensor pin definitions
#define MOTOR1_PIN 4
#define MOTOR2_PIN 5
#define SENSOR_PIN A0
#define BUZZER_PIN 14

// Initialize variables
int motorSpeed = 255;           // Maximum motor speed
int sensorValue = 0;            // Variable to store sensor reading
bool buzzerState = false;       // Tracks the buzzer's on/off state

// Blynk virtual pin actions
BLYNK_WRITE(V1) {               // Virtual pin V1 controls Motor 1
  int motorState = param.asInt();
  digitalWrite(MOTOR1_PIN, motorState);
}

BLYNK_WRITE(V2) {               // Virtual pin V2 controls Motor 2
  int motorState = param.asInt();
  digitalWrite(MOTOR2_PIN, motorState);
}

BLYNK_WRITE(V3) {               // Virtual pin V3 toggles the buzzer
  buzzerState = param.asInt();
  digitalWrite(BUZZER_PIN, buzzerState);
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Configure pin modes
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to Wi-Fi and Blynk
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Blynk handles IoT communication
  Blynk.run();

  // Read sensor data and print it
  sensorValue = analogRead(SENSOR_PIN);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Adjust motor speed or other actions based on sensor input if needed
  delay(100);
}
