cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_synth)
pico_sdk_init()

add_executable(pico_synth
    src/main.c
    src/buttons.c
    src/waves.c
    src/led.c
)

target_link_libraries(pico_synth pico_stdlib hardware_pwm hardware_adc)
pico_add_extra_outputs(pico_synth)
