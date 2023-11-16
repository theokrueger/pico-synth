#ifndef BUTTON_H
#define BUTTON_H

#include "hardware/gpio.h"
#include "hardware/adc.h"

// buttons store their state next update, pots always store
typedef struct {
    bool jsb;
    uint64_t jsb_cd;
    uint32_t fret_state;
    uint64_t last_read;
    bool signal;
} Input;

Input *setup_input();

void update_input(Input *inp, int t_ms);

#endif