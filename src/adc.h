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
#define NUM_ADC_CHANNELS (3)
#define ADC_BUFFER_SIZE (NUM_ADC_CHANNELS*2)

struct adc_dt_channels {
    struct adc_dt_spec channel_0;
    struct adc_dt_spec channel_1;
    struct adc_dt_spec channel_2;
};


// Grouping the motor pins for the excavator together 

//Struct definitions

//Variable Definitions
extern bool adcFinished;

// Function prototypes
int initADCChannels(struct adc_dt_channels *adc_channels);
enum adc_action my_adc_sequence_callback(const struct device *dev, const struct adc_sequence *sequence, uint16_t sampling_index);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_H */