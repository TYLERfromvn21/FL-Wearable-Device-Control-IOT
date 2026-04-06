#include <Arduino.h>
#include "alert_manager.h"
#include "config.h"
#include "globals.h"

// ==========================================
// TASK: MANAGE BUZZER & LED
// ==========================================
void TaskAlertManager(void *pvParameters) {
  for (;;) {
    if (alertTriggered) {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW); 
      vTaskDelay(pdMS_TO_TICKS(200));

      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH); 
      vTaskDelay(pdMS_TO_TICKS(200));
    } else {
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}