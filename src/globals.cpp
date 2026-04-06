#include "globals.h"

// Initialize shared variables
volatile int currentBPM = 72;         // Default resting heart rate
volatile int currentActivity = 0;     // 0=Resting, 1=Light Walk, 2=Brisk Walk, 3=Jogging, 4=Running
volatile bool alertTriggered = false; // Flag controlled by Python AI via Serial