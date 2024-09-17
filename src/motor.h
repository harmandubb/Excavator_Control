/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef MOTOR_H
#define MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

//#includes

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h> 
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree.h>


//#defines

#define PWM_FREQEUNCY (100000)
#define PMW_PERIOD (10000) //ns

// Grouping the motor pins for the excavator together 
#define BUCKET_PIN1 (15)
#define BUCKET_PIN2 (14)
#define BUCKET_PWM (13)

#define ARM_PIN1 (12)
#define ARM_PIN2 (21)
#define ARM_PWM (10)

#define BOOM_PIN1 (8)
#define BOOM_PIN2 (7)
#define BOOM_PWM (6)

//Struct definitions

// Define a typedef for the motor PWM specs structure
typedef struct {
    struct pwm_dt_spec pwm_motor0;
    struct pwm_dt_spec pwm_motor1;
    struct pwm_dt_spec pwm_motor2;
} motor_pwm_specs_t;  // This typedef allows us to use "motor_pwm_specs_t" instead of "struct motor_pwm_specs"

// Function prototypes

motor_pwm_specs_t init_pwm_motors(void);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* MOTOR_H */