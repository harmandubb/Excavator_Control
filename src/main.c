#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree.h>

#include "motor.h"

#define GPIO0_PORT DT_NODELABEL(gpio0)
#define GPIO1_PORT DT_NODELABEL(gpio1)

#define PWM_LED0        DT_ALIAS(pwm_motor0)

LOG_MODULE_REGISTER(Main, LOG_LEVEL_INF);

// struct pwm_dt_spec pwm_dt; 

const struct device *gpio0_dt; 
const struct device *gpio1_dt; 




int main(void)
{
        gpio1_dt = DEVICE_DT_GET(GPIO1_PORT);
        if (gpio1_dt == NULL) {
                LOG_ERR("Failed to get GPIO device binding\n");
        } else {
                LOG_INF("GPIO device binding success\n");
        }

        static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);
        // if (!device_is_ready(pwm_dt.dev)) {
        //         LOG_ERR("PWM device not ready\n");
        // } else {
        //         LOG_INF("PWM device ready\n");
        // }



        return 0;
}
