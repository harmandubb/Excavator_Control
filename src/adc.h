/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

//#includes

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h> 
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include "sensor.h"
#include <zephyr/drivers/adc.h>


//#defines


// Grouping the motor pins for the excavator together 

//Struct definitions

// Function prototypes


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_H */