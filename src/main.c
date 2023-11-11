#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
    /// \tag::setup_pwm[]

    // GPIO 1 setup
    gpio_set_function(0, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(0);

    float lowest = 95.375f;
    float highest = 0.125f;

    // pwm clock freq
    pwm_set_clkdiv(slice_num, lowest / 16);
    pwm_set_wrap(slice_num, 65465);
    pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]
    int div = 1000;
        pwm_set_chan_level(slice_num, PWM_CHAN_A, div);
    int delt = 100;
//    while (1) {
//        float n = div + delt;
//        if (n < 1000 || n > 64000) delt *= -1;
//        pwm_set_chan_level(slice_num, PWM_CHAN_A, div);
////        pwm_set_clkdiv(slice_num, div+=delt);
//        sleep_ms(100);
//    }
    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
}
