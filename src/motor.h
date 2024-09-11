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

//Struct definitions

// Function prototypes


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* MOTOR_H */