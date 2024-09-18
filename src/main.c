#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree.h>

#include "motor.h"
#include "adc.h"

#define GPIO0_PORT DT_NODELABEL(gpio0)
#define GPIO1_PORT DT_NODELABEL(gpio1)

LOG_MODULE_REGISTER(Main, LOG_LEVEL_INF);

// struct pwm_dt_spec pwm_dt; 

const struct device *gpio0_dt; 
const struct device *gpio1_dt; 




int main(void)
{
        int err = 0; 

        //flags 
        extern bool adcFinished; 
        extern uint64_t last_time;

        gpio1_dt = DEVICE_DT_GET(GPIO1_PORT);
        if (gpio1_dt == NULL) {
                LOG_ERR("Failed to get GPIO device binding\n");
        } else {
                LOG_INF("GPIO device binding success\n");
        }

        int cp1_arr[] = {BUCKET_PIN1, ARM_PIN1, BOOM_PIN1};
        int cp2_arr[] = {BUCKET_PIN2, ARM_PIN2, BOOM_PIN2};

        motor_pwm_specs_t motors_pwm = initArmMotors(gpio1_dt,cp1_arr, cp2_arr,NUM_ARM_MOTORS);

        const struct device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));

        struct adc_dt_channels adc_channels;  
        err = initADCChannels(&adc_channels);
        if (err < 0) {
                LOG_ERR("Failed to initialize ADC channels");
        } else {
                LOG_INF("ADC channels successfully initialized");
        }

        struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
                
        };

        uint8_t adc_buf[ADC_BUFFER_SIZE] = {0};

        struct adc_sequence sequence = {
		.buffer = &adc_buf,
		.buffer_size = sizeof(adc_buf),
		//Optional
		//.calibrate = true, //turn on calibration after the bare minimum code is active
                .options = &opts,
                .channels = (1 << NUM_SENSORS) - 1,
                .resolution = 12,
	};

        err = adc_read(adc_dev, &sequence);
        if (err < 0) {
                LOG_ERR("Could not read (%d)", err);
                return -1; 
        }

        while(!adcFinished);
        LOG_INF("ADC INITALIZATION DONE\n"); 

        PID_timer_setup();




        return 0;
}
