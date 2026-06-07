#pragma once
#include "config.h"
// --- SHARED GLOBAL VARIABLES ---
extern volatile int currentBPM;
extern volatile int currentActivity;
extern volatile bool alertTriggered;

// --- ACCELEROMETER DATA ---
extern volatile float acc_x;
extern volatile float acc_y;
extern volatile float acc_z;

// --- HEART RATE WINDOW ---
extern volatile float hr_window[HR_WINDOW_SIZE];
extern volatile int hr_window_index;