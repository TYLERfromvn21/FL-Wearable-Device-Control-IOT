#include <Arduino.h>
#include "pulse_sensor.h"
#include "config.h"
#include "globals.h"

// ==========================================
// TASK: READ PULSE SENSOR
// ==========================================
void TaskReadPulse(void *pvParameters) {
  int threshold = 2400; 
  bool belowThreshold = true;
  unsigned long lastBeatTime = 0;

  for (;;) {
    int signal = analogRead(PULSE_PIN);
    unsigned long currentTime = millis();

    // Basic Peak Detection Algorithm
    if (signal > threshold && belowThreshold) {
      belowThreshold = false;
      unsigned long delta = currentTime - lastBeatTime;
      lastBeatTime = currentTime;

      // Filter out noise: Only accept BPM between 30 and 200
      if (delta > 300 && delta < 2000) {
        int instantBPM = 60000 / delta;
        currentBPM = (currentBPM + instantBPM) / 2; // Moving average for smoothing

        // --- Test buzzer (Uncomment for testing) ---
         if (currentBPM > 120) alertTriggered = true; else alertTriggered = false;
      }
    } else if (signal < threshold - 100) {
      belowThreshold = true;
    }

    vTaskDelay(pdMS_TO_TICKS(20)); // Sample at 50Hz (every 20ms)
  }
}