#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "motion_sensor.h"
#include "globals.h"

// Create MPU6050 sensor object
Adafruit_MPU6050 mpu;

// ==========================================
// TASK: READ MOTION SENSOR (MPU6050)
// ==========================================
void TaskReadMotion(void *pvParameters) {
  
  // Initialize I2C communication for MPU6050
  if (!mpu.begin()) {
    Serial.println("ERROR: MPU6050 not found. Motion task halted!");
    while (1) { vTaskDelay(10); } // Halt here if sensor is disconnected
  }
  
  Serial.println("MPU6050 initialized successfully!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  for (;;) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Store raw accelerometer data
    acc_x = a.acceleration.x;
    acc_y = a.acceleration.y;
    acc_z = a.acceleration.z;

    // Calculate total acceleration magnitude
    float magnitude = sqrt(acc_x * acc_x + 
                           acc_y * acc_y + 
                           acc_z * acc_z);

    // Calculate motion level (subtract 9.8 m/s^2 of gravity)
    float motionLevel = abs(magnitude - 9.8);

    // Classify activity level to send to output
    if (motionLevel < 2.0) {
      currentActivity = 0; // Resting or slight movement
    } else if (motionLevel < 5.0) {
      currentActivity = 1; // Light Walk
    } else if (motionLevel < 8.0) {
      currentActivity = 2; // Brisk Walk
    } else {
      currentActivity = 4; // Running or vigorous shaking
    }

    vTaskDelay(pdMS_TO_TICKS(500)); // Update motion data every 0.5 seconds
  }
}