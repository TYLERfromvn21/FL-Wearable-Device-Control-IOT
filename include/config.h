#pragma once

// --- HARDWARE PINS ---
#define PULSE_PIN 32     // Analog pin for Pulse Sensor (ADC1 is required)
#define BUZZER_PIN 27    // Pin for Buzzer alarm
#define LED_RED_PIN 2    // Pin for Red LED indicator

// --- RESERVED FOR MOTION SENSOR ---
#define MOTION_PIN 34    // Reserved for Analog/Digital motion sensor later

// ==========================================
// --- CORE IOT TEST CONFIGURATION START ---
// TODO: Comment out this entire section when moving to Final Python AI Mode
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

#define MQTT_SERVER "mqtt.coreiot.io"         // Or your university's Core IoT IP
#define MQTT_PORT 1883
#define MQTT_TOKEN "YOUR_DEVICE_ACCESS_TOKEN" // Paste your Core IoT device token here
// --- CORE IOT TEST CONFIGURATION END ---
// ==========================================