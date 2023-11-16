#include "buttons.h"
#include "hardware.h"

#include <stdlib.h>

#include "pico/stdlib.h"

#define COOLDOWN 500


Input *setup_input() {
    // defs
    Input *inp = (Input *) malloc(sizeof(Input));
    inp->jsb = false;

    // button
    for (int i = 4; i <= 15; ++i) {
        gpio_init(i);
    }

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

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
