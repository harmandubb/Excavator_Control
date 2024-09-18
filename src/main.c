#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree.h>

#include "motor.h"

#define GPIO0_PORT DT_NODELABEL(gpio0)
#define GPIO1_PORT DT_NODELABEL(gpio1)

LOG_MODULE_REGISTER(Main, LOG_LEVEL_INF);

// struct pwm_dt_spec pwm_dt; 

const struct device *gpio0_dt; 
const struct device *gpio1_dt; 




int main(void)
{
        int err = 0; 
        
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

        err = initADCChannels();


        return 0;
}
