/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C" {
#endif

//#includes

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h> 
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>


//#defines

//variables 
extern uint64_t last_time;

//Struct definitions
typedef struct {
    float Kp;  // Proportional gain
    float Ki;  // Integral gain
    float Kd;  // Derivative gain
    float prev_error;   // Error from the previous step
    float integral;     // Integral accumulator
    float integral_max; // Maximum limit for the integral term
    float integral_min; // Minimum limit for the integral term
} PIDController;

// Function prototypes
void PID_Init(PIDController *pid, float Kp, float Ki, float Kd, float integral_min, float integral_max);
float PID_Compute(PIDController *pid, float setpoint, float measured_value, float dt);\
void timer_setup(void);
uint64_t get_elapsed_time(void);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* PID_H */