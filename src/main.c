/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "pico/stdlib.h"
#include "hardware/pwm.h"

uint32_t pwm_set_freq_duty(uint slice_num,
                           uint chan, uint32_t f, int d) {
    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 +
                         (clock % (f * 4096) != 0);
    if (divider16 / 16 == 0)
        divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16,
                            divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}

int main() {
    /// \tag::setup_pwm[]

    // GPIO 1 setup
    gpio_set_function(0, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(0);
    uint chan = pwm_gpio_to_channel(0);
    pwm_set_enabled(slice_num, true);
    float lowest = 55;
    float highest = 3520;

    float pitch = lowest;
    float mult = 1.05946309436f;
    while (1) {
        float o = mult * pitch;
        if (o <= lowest || o >= highest) {
            mult = 1 / mult;
        }
        pitch *= mult;
        pwm_set_freq_duty(slice_num, chan, pitch, 50);
        sleep_ms(500);
    }
}
