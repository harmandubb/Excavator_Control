#include "adc.h"

LOG_MODULE_REGISTER(ADC, LOG_LEVEL_INF);

//Global Variables

/**
 * @brief Initializes and sets up x ADC channels.
 * 
 * 
 * @return 0 on success, -1 if any ADC channel is not ready or setup fails.
 * 
 * @note The ADC channels are retrieved from the device tree under the `zephyr_user` path.
 * 
 * The function performs the following:
 * - Initializes the x ADC channel and checks if it is ready. Sets it up if ready.
 * - Logs an error message and returns `-1` if any of the checks fail.
 * - Logs a success message and returns `0` if all channels are successfully initialized and set up.
 */

int initADCChannels(struct adc_dt_channels *adc_channels){
    *adc_channels = (struct adc_dt_channels){
        .channel_0 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0),
        .channel_1 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 1),
        .channel_2 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 2)
    };

    int err;

    // Check if the first ADC channel is ready and set it up
    if (!adc_is_ready_dt(&adc_channels->channel_0)) {
        LOG_ERR("ADC controller device %s not ready", adc_channels->channel_0.dev->name);
        return -1;  // Return an empty struct on error
    }
    err = adc_channel_setup_dt(&adc_channels->channel_0);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 0, err);
        return -1;  // Return an empty struct on error
    }

    // Check if the second ADC channel is ready and set it up
    if (!adc_is_ready_dt(&adc_channels->channel_1)) {
        LOG_ERR("ADC controller device %s not ready", adc_channels->channel_1.dev->name);
        return -1;  // Return an empty struct on error
    }
    err = adc_channel_setup_dt(&adc_channels->channel_1);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 1, err);
        return -1;  // Return an empty struct on error
    }

    // Check if the third ADC channel is ready and set it up
    if (!adc_is_ready_dt(&adc_channels->channel_2)) {
        LOG_ERR("ADC controller device %s not ready", adc_channels->channel_2.dev->name);
        return -1;  // Return an empty struct on error
    }
    err = adc_channel_setup_dt(&adc_channels->channel_2);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 2, err);
        return -1;  // Return an empty struct on error
    }

    LOG_INF("All ADC channels initialized and set up successfully");
    return 0;  // Return the initialized channels on success
};