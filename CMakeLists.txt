cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(nrf)

target_sources(app PRIVATE 
        src/main.c
        src/motor.c
        src/motor.h
        src/sensor.c
        src/sensor.h
        src/adc.c
        src/adc.h
        src/PID.c
        src/PID.h
        )
