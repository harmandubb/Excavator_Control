#include "adc.h"

LOG_MODULE_REGISTER(ADC, LOG_LEVEL_INF);

//Global Variables
static const struct adc_dt_spec adc_channels[NUM_SENSORS];

int initADCChannels(int num_channels){
    for (int i = 0; i < NUM_SENSORS; i++) {
        // Initialize each channel using the ADC_DT_SPEC_GET_BY_IDX macro
        adc_channels[i] = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), i);
    }
};

