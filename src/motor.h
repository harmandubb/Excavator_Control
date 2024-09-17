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

// Function prototypes


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* MOTOR_H */