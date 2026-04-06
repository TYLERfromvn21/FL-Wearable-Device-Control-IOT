#include <Arduino.h>
#include "comm_task.h"
#include "globals.h"

// ==========================================
// --- CORE IOT TEST INCLUDES & VARS START ---
// TODO: Comment out this block when moving to Final Python AI Mode
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
// --- CORE IOT TEST INCLUDES & VARS END ---
// ==========================================


// ==========================================
// --- CORE IOT CONNECTION FUNCTION START ---
// TODO: Comment out this entire function when moving to Final Python AI Mode
void connectToWiFiAndMQTT() {
  // 1. Connect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(pdMS_TO_TICKS(500));
      Serial.print(".");
    }
    Serial.println(" Connected!");
  }

  // 2. Connect to Core IoT via MQTT
  if (!mqttClient.connected()) {
    Serial.print("Connecting to Core IoT...");
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    
    // Core IoT uses the Access Token as the username
    if (mqttClient.connect("ESP32_Wearable", MQTT_TOKEN, "")) {
      Serial.println(" Connected!");
    } else {
      Serial.print(" Failed, rc=");
      Serial.println(mqttClient.state());
    }
  }
}
// --- CORE IOT CONNECTION FUNCTION END ---
// ==========================================


// ==========================================
// TASK: SERIAL & MQTT COMMUNICATION
// ==========================================
void TaskCommunicate(void *pvParameters) {
  for (;;) {
    
    // ==========================================
    // --- CORE IOT DATA PUBLISH START ---
    // TODO: Comment out this block when moving to Final Python AI Mode
    connectToWiFiAndMQTT();
    mqttClient.loop();

    if (mqttClient.connected()) {
      // Create JSON payload format: {"bpm": 85, "activity": 0}
      String payload = "{\"bpm\":";
      payload += currentBPM;
      payload += ",\"activity\":";
      payload += currentActivity;
      payload += "}";

      // Publish data to Core IoT telemetry topic
      mqttClient.publish("v1/devices/me/telemetry", payload.c_str());
    }
    // --- CORE IOT DATA PUBLISH END ---
    // ==========================================


    // 1. SEND DATA TO PYTHON VIA SERIAL (Keep this running!)
    // Format: BPM,Activity
    Serial.print(currentBPM);
    Serial.print(",");
    Serial.println(currentActivity);

    // 2. LISTEN FOR ALERT COMMANDS FROM PYTHON (Keep this running!)
    if (Serial.available() > 0) {
      char cmd = Serial.read();
      if (cmd == 'A') {
        alertTriggered = true;  // High risk detected by AI!
      } else if (cmd == 'O') {
        alertTriggered = false; // Safe condition!
      }
    }

    vTaskDelay(pdMS_TO_TICKS(1000)); // Update and send data every 1 second
  }
}