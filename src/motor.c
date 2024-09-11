#include "motor.h"

LOG_MODULE_REGISTER(Motor, LOG_LEVEL_INF);

//Global Variables

/**
 * @brief enable the pins and outputs for one motor (two input pins and 1 pwm pin)
 * 
 * @param struct device *gpio_dt: struct holding gpio device tree information
 * @param struct pwm_dt_spec: struct holding pwm device tree config information
 * @param int control_pin1
 * @param int control_pin2
 * @param int pwm_pin
 * 
 * @return error if present
 */

int motorSetup(struct device *gpio_dt, struct pwm_dt_spec pwm_dt, int control_pin1, int control_pin2, int pwm_pin){
    int err = 0;
    gpio_flags_t control_pin_flags = GPIO_OUTPUT_LOW;
    //initialize the gpio as needed 

    err = gpio_pin_configure(gpio_dt, control_pin1, GPIO_OUTPUT);
    if (err < 0) {
        printk("Error configuring control_pin1\n");
        return err;
    }

    err = gpio_pin_configure(gpio_dt, control_pin2, GPIO_OUTPUT);
    if (err < 0) {
        printk("Error configuring control_pin2\n");
        return err;
    }

     // Configure PWM
    if (!device_is_ready(pwm_dt.dev)) {
        printk("Error: PWM device is not ready\n");
        return -ENODEV;
    }
    

    // Initialize PWM with 0% duty cycle (motor stopped)
    err = pwm_set_dt(&pwm_dt, PMW_PERIOD, 0);
    if (err < 0) {
        printk("Error initializing PWM\n");
        return err;
    }

    printk("Motor setup completed successfully\n");
    return 0;

};