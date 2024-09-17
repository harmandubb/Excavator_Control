#include "motor.h"

LOG_MODULE_REGISTER(Motor, LOG_LEVEL_INF);

//Global Variables
motor_pwm_specs_t motors;

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

static int motorSetup(struct device *gpio_dt, int control_pin1, int control_pin2){
    int err = 0;
    //initialize the gpio as needed 

    err = gpio_pin_configure(gpio_dt, control_pin1, GPIO_OUTPUT_LOW);
    if (err < 0) {
        printk("Error configuring control_pin1\n");
        return err;
    }

    err = gpio_pin_configure(gpio_dt, control_pin2, GPIO_OUTPUT_LOW);
    if (err < 0) {
        printk("Error configuring control_pin2\n");
        return err;
    }

    LOG_INF("Motor control pin setup completed successfully\n");
    return 0;

};

/**
 * @brief gets struct of motor pwm pins set to be used
 * 
 * @return motor_pwm_specs_t return of all of the amr movement motors
 */

static motor_pwm_specs_t init_pwm_motors(void)
{
    // Initialize the motors from DeviceTree using the correct method of initialization
    motor_pwm_specs_t motors = {
        .pwm_motor0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_motor0)),
        .pwm_motor1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_motor1)),
        .pwm_motor2 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_motor2))
    };

    // Check if all PWM devices are ready
    if (!device_is_ready(motors.pwm_motor0.dev)) {
        LOG_ERR("PWM Motor 0 device is not ready");
    }
    if (!device_is_ready(motors.pwm_motor1.dev)) {
        LOG_ERR("PWM Motor 1 device is not ready");
    }
    if (!device_is_ready(motors.pwm_motor2.dev)) {
        LOG_ERR("PWM Motor 2 device is not ready");
    }

    LOG_INF("All PWM motors initialized and ready");

    // Return the structure containing the initialized PWM motors
    return motors;
};

/** @brief Single function to fully initialize all motor pins for the arm (control + pwm)
 *  
 *  @param struct device *gpio_dt: struct holding gpio device tree information for the control pins 
 *  @param int cp1_arr : Array holding control pin 1 for the motors to activiate 
 *  @param int cp2_arr : Arry holding control pin 2 for the motors to activate 
 *  @param int num_motors: number of motors to activate in this funciton
 *  
 *  @return motor_pwm_specs_t struct containing all of the motor dt specs  
 * 
 */

motor_pwm_specs_t initArmMotors(struct device *gpio_dt, int cp1_arr[], int cp2_arr[], int num_motors){

    for(int i = 0; i < num_motors; i++){
        motorSetup(gpio_dt, cp1_arr[i], cp2_arr[i]);
    }

    return init_pwm_motors();
};

/** @brief update pwm duty cycle of arm motors 
 * 
 *  @param motor_pwm_specs_t struct containing all of the arm motor dt specs
 *  @param bucket_duty_cycle
 *  @param arm_duty_cycle
 *  @param boom_duty_cycle
 * 
 *  @return error if present
 */

int updateArmDutyCycles(motor_pwm_specs_t *motors, int bucket_duty_cycle, int arm_duty_cycle, int boom_duty_cycle) {
    int err = 0;

    // Set PWM for bucket motor
    err = pwm_set_pulse_dt(&(motors->pwm_motor0), bucket_duty_cycle);
    if (err < 0) {
        LOG_ERR("Failed to set bucket motor PWM: %d", err);
        return err;  // Return error code if setting PWM failed
    }

    // Set PWM for arm motor
    err = pwm_set_pulse_dt(&(motors->pwm_motor1), arm_duty_cycle);
    if (err < 0) {
        LOG_ERR("Failed to set arm motor PWM: %d", err);
        return err;  // Return error code if setting PWM failed
    }

    // Set PWM for boom motor
    err = pwm_set_pulse_dt(&(motors->pwm_motor2), boom_duty_cycle);
    if (err < 0) {
        LOG_ERR("Failed to set boom motor PWM: %d", err);
        return err;  // Return error code if setting PWM failed
    }

    LOG_INF("Motor duty cycles updated successfully");

    return 0;  // Return 0 on success
}

