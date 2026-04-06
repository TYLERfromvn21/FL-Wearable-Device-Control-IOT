#include <Arduino.h>
#include "motion_sensor.h"
#include "globals.h"

// ==========================================
// TASK: READ MOTION SENSOR
// ==========================================
void TaskReadMotion(void *pvParameters) {
  for (;;) {
    /* TODO: PLACEHOLDER FOR MOTION SENSOR 
       Depending on the sensor acquired later, implement logic here:
       - MPU6050 (I2C): Read X, Y, Z acceleration, calculate magnitude.
       - ADXL335 (Analog): Read via analogRead().
       - SW-420 (Digital): Read via digitalRead().
    */
    
    // Temporary hardcoded value (0 = Resting)
    currentActivity = 0; 

    vTaskDelay(pdMS_TO_TICKS(500)); // Read motion data every 0.5 seconds
  }
}