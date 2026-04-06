#include <Arduino.h>
#include "config.h"
#include "pulse_sensor.h"
#include "motion_sensor.h"
#include "comm_task.h"
#include "alert_manager.h"

// --- TASK HANDLES ---
TaskHandle_t PulseTask;
TaskHandle_t MotionTask;
TaskHandle_t CommTask;
TaskHandle_t AlertTask;

// ==========================================
// SYSTEM SETUP
// ==========================================
void setup() {
  Serial.begin(115200);
  
  // Initialize Hardware Pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PULSE_PIN, INPUT);
  // pinMode(MOTION_PIN, INPUT); // Uncomment later if using Analog/Digital motion sensor

  // Set initial safe states
digitalWrite(LED_RED_PIN, LOW);
digitalWrite(BUZZER_PIN, HIGH); 

  Serial.println("Wearable Local System Started...");

  // Create FreeRTOS Tasks
  xTaskCreatePinnedToCore(TaskReadPulse, "PulseTask", 2048, NULL, 2, &PulseTask, 0);
  xTaskCreatePinnedToCore(TaskReadMotion, "MotionTask", 2048, NULL, 1, &MotionTask, 0);
  xTaskCreatePinnedToCore(TaskCommunicate, "CommTask", 2048, NULL, 1, &CommTask, 1);
  xTaskCreatePinnedToCore(TaskAlertManager, "AlertTask", 2048, NULL, 2, &AlertTask, 1);
}

void loop() {
  // FreeRTOS manages everything in the background.
  // Leave the loop empty.
}