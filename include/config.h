#pragma once

// --- HARDWARE PINS ---
#define PULSE_PIN 32     // Analog pin for Pulse Sensor (ADC1 is required)
#define HR_WINDOW_SIZE 10 // Number of heart rate values to store in the window
#define BUZZER_PIN 27    // Pin for Buzzer alarm
#define LED_RED_PIN 2    // Pin for Red LED indicator

// --- RESERVED FOR MOTION SENSOR ---
#define MOTION_PIN 34    // Reserved for Analog/Digital motion sensor later

// ==========================================
// --- CORE IOT TEST CONFIGURATION START ---
// --- WI-FI CONFIGURATION ---
//#define WIFI_SSID "LAPTOP-8J75CQDF 6204"
//#define WIFI_PASS "12345678"

#define MQTT_SERVER "broker.hivemq.com"        
#define MQTT_PORT 1883
#define MQTT_TOKEN "" // Paste your Core IoT device token here
// --- CORE IOT TEST CONFIGURATION END ---
// ==========================================