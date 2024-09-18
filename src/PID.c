#include "PID.h"

// Function to initialize the PID controller
void PID_Init(PIDController *pid, float Kp, float Ki, float Kd, float integral_min, float integral_max) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prev_error = 0;
    pid->integral = 0;
    pid->integral_min = integral_min;
    pid->integral_max = integral_max;
}

// PID control function
float PID_Compute(PIDController *pid, float setpoint, float measured_value, float dt) {
    // Calculate error
    float error = setpoint - measured_value;

    // Calculate the proportional term
    float proportional = pid->Kp * error;

    // Calculate the integral term with clamping (anti-windup)
    pid->integral += error * dt;
    
    // Apply integral clamping
    if (pid->integral > pid->integral_max) {
        pid->integral = pid->integral_max;
    } else if (pid->integral < pid->integral_min) {
        pid->integral = pid->integral_min;
    }
    
    float integral = pid->Ki * pid->integral;

    // Calculate the derivative term
    float derivative = (error - pid->prev_error) / dt;
    float derivative_term = pid->Kd * derivative;

    // Update previous error
    pid->prev_error = error;

    // Compute the final output
    float output = proportional + integral + derivative_term;

    return output;
}