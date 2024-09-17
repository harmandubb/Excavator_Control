#include "sensor.h"

LOG_MODULE_REGISTER(Sensor, LOG_LEVEL_INF);

//Global Variables


/** @brief Sets up a sensor pin for input 
 * 
 *  @param struct device gpio_dt: device tree spec for the gpio group used
 *  @param int sensor_pin
 * 
 *  @param Error if present
 * 
 */
static int sensorSetup(struct device *gpio_dt, int sensor_pin) {
    int err = 0;

    // Initialize the GPIO pin as input for the sensor
    err = gpio_pin_configure(gpio_dt, sensor_pin, GPIO_INPUT);
    if (err < 0) {
        printk("Error configuring sensor_pin\n");
        return err;
    }

    LOG_INF("Sensor pin setup completed successfully\n");
    return 0;
};

/**
 * @brief Initialize an array of sensor pins as input.
 *
 *
 * @param gpio_dt Pointer to the GPIO device structure.
 * @param sensor_pins Array of sensor pin numbers to be initialized as inputs.
 * @param num_pins Number of sensor pins in the array.
 *
 * @retval 0 If all sensor pins are configured successfully.
 * @retval -EINVAL If one of the sensor pin configurations fails.
 */

int sensorArraySetup(struct device *gpio_dt, int *sensor_pins, int num_pins) {
    int err = 0;

    // Loop through the array of sensor pins and initialize each one
    for (int i = 0; i < num_pins; i++) {
        err = sensorSetup(gpio_dt, sensor_pins[i]);
        if (err < 0) {
            LOG_ERR("Error configuring sensor pin %d\n", sensor_pins[i]);
            return err;
        }
    }

    LOG_INF("All sensor pins setup completed successfully\n");
    return 0;
}

