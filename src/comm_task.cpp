#include <Arduino.h>
#include "comm_task.h"
#include "globals.h"

// ==========================================
// --- CORE IOT TEST INCLUDES & VARS START ---
#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
// --- CORE IOT TEST INCLUDES & VARS END ---
// ==========================================

// ==========================================
// --- CORE IOT CONNECTION FUNCTION START ---
void connectToWiFiAndMQTT() {
  // 1. Smart WiFi Management using WiFiManager
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Starting WiFiManager...");
    WiFiManager wifiManager;
    bool res = wifiManager.autoConnect("Vital-Bracer-Setup");

    if(!res) {
      Serial.println("Failed to connect to WiFi, retrying...");
    } else {
      Serial.println("WiFi connected successfully!");
    }
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
      // Create JSON payload format with all sensor data
      // {"bpm": 85, "activity": 0, "acc_x": 1.2, "acc_y": 3.4, "acc_z": 5.6, "hr_window": [70, 72, 75, ..., N]}
      // String payload = "{\"bpm\":";
      // payload += String(currentBPM);
      // payload += ",\"activity\":";
      // payload += String(currentActivity);
      // payload += ",\"acc_x\":";
      // payload += String(acc_x, 2); // 2 decimal places
      // payload += ",\"acc_y\":";
      // payload += String(acc_y, 2); // 2 decimal places
      // payload += ",\"acc_z\":";
      // payload += String(acc_z, 2); // 2 decimal places
      // payload += ",\"battery\":100";
      // payload += ",\"hr_window\":[";
      // for (int i = 0; i < HR_WINDOW_SIZE; i++) {
      //   payload += String(hr_window[i], 0); // Format as integer for heart rate
      //   if (i < HR_WINDOW_SIZE - 1) {
      //     payload += ",";
      //   }
      // }
      // payload += "]}";
      // Create JSON payload format matching Flutter's SensorPacket expectations
      String payload = "{";
      payload += "\"device_id\":\"ESP32_Wearable\",";
      payload += "\"heart_rate\":"; 
      payload += String(currentBPM);
      payload += ",\"device_activity_code\":";
      payload += String(currentActivity);
      payload += ",\"acc_x\":";
      payload += String(acc_x, 2);
      payload += ",\"acc_y\":";
      payload += String(acc_y, 2);
      payload += ",\"acc_z\":";
      payload += String(acc_z, 2);
      payload += ",\"battery\":100";
      payload += ",\"hr_window\":[";
      for (int i = 0; i < HR_WINDOW_SIZE; i++) {
        payload += String(hr_window[i], 0);
        if (i < HR_WINDOW_SIZE - 1) {
          payload += ",";
        }
      }
      payload += "]}";

      // Publish data to App
      mqttClient.publish("wearable/data", payload.c_str());
    }
    // --- CORE IOT DATA PUBLISH END ---
    // ==========================================


    // 1. SEND DATA TO PYTHON VIA SERIAL (Keep this running!)
    // Format: BPM,Activity,AccX,AccY,AccZ,HR1,HR2,HR3,HR4,HR5
    Serial.print(currentBPM);
    Serial.print(",");
    Serial.print(currentActivity);
    Serial.print(",");
    Serial.print(acc_x, 2); // 2 decimal places
    Serial.print(",");
    Serial.print(acc_y, 2); // 2 decimal places
    Serial.print(",");
    Serial.print(acc_z, 2); // 2 decimal places
    for (int i = 0; i < HR_WINDOW_SIZE; i++) {
      Serial.print(",");
      Serial.print(hr_window[i], 0); // Format as integer for heart rate
    }
    Serial.println();

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