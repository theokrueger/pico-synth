/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <hardware/pwm.h>
#include "pico/stdlib.h"

const int32_t sampling_rate = 44000;
const int32_t interval_us = 1000000 / sampling_rate;
/// \tag::timer_example[]
volatile bool timer_fired = false;
int counter = 0;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
uint slice_num;
const int hz = 471;

bool repeating_timer_callback(struct repeating_timer *t) {
    counter++;
    if ((counter * 2 * hz / sampling_rate) % 2) {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, 8000);
    } else{
        pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    }
    return true;
}

int main() {
//    const double freq = 44000;
    stdio_init_all();
    slice_num = pwm_gpio_to_slice_num(0);
//    gpio_init(LED_PIN);
//    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_function(0, GPIO_FUNC_PWM);
    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 16000);
    // Set channel A output high for two cycle before dropping
    pwm_set_enabled(slice_num, true);


    // Create a repeating timer that calls repeating_timer_callback.
    // If the delay is > 0 then this is the delay between the previous callback ending and the next starting.
    // If the delay is negative (see below) then the next call to the callback will be exactly 500ms after the
    // start of the call to the last callback
    struct repeating_timer timer;
    add_repeating_timer_us(-interval_us, repeating_timer_callback, NULL, &timer);
    sleep_ms(10000);
    bool cancelled = cancel_repeating_timer(&timer);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    sleep_ms(2000);
    return 0;
}
/// \end::timer_example[]