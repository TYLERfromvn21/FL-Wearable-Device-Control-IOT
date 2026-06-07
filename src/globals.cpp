#include "globals.h"

// Initialize shared variables
volatile int currentBPM = 72;         // Default resting heart rate
volatile int currentActivity = 0;     // 0=Resting, 1=Light Walk, 2=Brisk Walk, 3=Jogging, 4=Running
volatile bool alertTriggered = false; // Flag controlled by Python AI via Serial

// Initialize accelerometer data
volatile float acc_x = 0.0;
volatile float acc_y = 0.0;
volatile float acc_z = 0.0;

// Initialize heart rate window
volatile float hr_window[HR_WINDOW_SIZE] = {72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0};
volatile int hr_window_index = 0;