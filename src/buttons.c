#include "buttons.h"
#include "hardware.h"

#include <stdlib.h>

#include "pico/stdlib.h"

#define COOLDOWN 500


Input *setup_input() {
    // defs
    Input *inp = (Input *) malloc(sizeof(Input));
    inp->jsb = false;
    inp->jsx = 0.0f;
    inp->jsy = 0.0f;

    // button
    for (int i = 4; i <= 15; ++i) {
        gpio_init(i);
    }

    // adc
    adc_init();
    adc_gpio_init(JSX_GPIO);
    adc_gpio_init(JSY_GPIO);
    return inp;
}

void get_inputs(Input *inp, uint64_t t_ms) {
    /* JOYSTICK */
    // joystick button
//    if (inp->jsb_cd + COOLDOWN < t_ms) {
//        inp->jsb_cd = t_ms;
    bool next = gpio_get(JSB_GPIO);
    inp->signal = !inp->jsb && next;
    inp->jsb = next;
//    }
    // joystick x
    adc_select_input(JSX_ADC);
    inp->jsx = adc_read();

    // joystick y
//    adc_select_input(JSY_ADC);
//    inp->jsy = ADC_FLOAT;
    inp->fret_state = 0;
    for (int i = 4; i <= 15; ++i) {
        inp->fret_state |= gpio_get(i) << i;
    }
    inp->fret_state ^= 1 << 12;
    return;
}

void update_data(Input *inp) {
    // jsx -> freq
    // wv->hz = inp->jsx * LVL_MAX;
    return;
}

void update_input(Input *inp, int t_ms) {
    get_inputs(inp, t_ms);
    update_data(inp);
    return;
}
