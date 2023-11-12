#include "waves.h"
#include "hardware.h"
#define M_PI 3.14159265358979323846
#define CHANNELS 4
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/pwm.h"
#include "led.h"
#include "pico/stdlib.h"

#define AUD_OUT 0

Wave *setup_wave() {
    Wave *wv = (Wave *)malloc(sizeof(Wave));
    stdio_init_all();
    wv->mult = 8;
    // local use only (ugly)
    wv->loc = (WV_LOC *)malloc(sizeof(WV_LOC));
    wv->loc->sampling_rate = 44000;
    wv->sleep_us = 1000 * 1000 / wv->loc->sampling_rate;
    wv->loc->t = 0;
    wv->loc->i = 0;
    // params we change
//     wv->hz = (int)(840.0f * pow(HALFSTEP, 3));  // calibrate per speaker for some reason????
    wv->type = SquareWave;

    // gpio setup
    wv->loc->slice_num = pwm_gpio_to_slice_num(AUD_OUT);
    gpio_set_function(AUD_OUT, GPIO_FUNC_PWM);
    pwm_set_wrap(wv->loc->slice_num, WRAP);
    pwm_set_enabled(wv->loc->slice_num, true);
    return wv;
}

// Returns a value between 0 and 1.0 that denotes the amp of the wave
float get_level(Wave *wv, float newhz){
        newhz *= wv->mult;
        switch (wv->type) {
        case SineWave:
            return (1 - cosf(2 * 1.565 * M_PI * newhz * wv->loc->i /
                              wv->loc->sampling_rate)) / 2 ;
        case SquareWave:
                return ((int)(wv->loc->i * 2*  newhz / wv->loc->sampling_rate) % 2);  
            break;
        case SawWave:
            break;
        default:
            // error
            SET_LED_ON();
            break;
    };
    return 0;
}
void update_wave(Wave *wv, Input *inp) {
    float level = 0;
    // printf("%f\n", inp->jsx);
    // if (inp->jsx) {// Place holder condition
    //     if(inp->jsx < 0 && wv->mult > 1){
    //             wv->mult >>= 1;
    //     }else if(inp->jsx > 0 && wv->mult < 256){
    //             wv->mult <<= 1;
    //     }
    // }
    if (inp->fret_state) {
        if(inp->fret_state & (1 << 4)) level += get_level(wv, FREQ_C);
        if(inp->fret_state & (1 << 8)) level += get_level(wv, FREQ_CS);
        if(inp->fret_state & (1 << 12)) level += get_level(wv, FREQ_D);
        if(inp->fret_state & (1 << 11)) level += get_level(wv, FREQ_DS);
        if(inp->fret_state & (1 << 13)) level += get_level(wv, FREQ_E);
        if(inp->fret_state & (1 << 10)) level += get_level(wv, FREQ_F);
        if(inp->fret_state & (1 << 6)) level += get_level(wv, FREQ_FS);
        if(inp->fret_state & (1 << 5)) level += get_level(wv, FREQ_G);
        if(inp->fret_state & (1 << 7)) level += get_level(wv, FREQ_GS);
        if(inp->fret_state & (1 << 14)) level += get_level(wv, FREQ_A);
        if(inp->fret_state & (1 << 15)) level += get_level(wv, FREQ_AS);
        if(inp->fret_state & (1 << 9)) level += get_level(wv, FREQ_B);
    }

//     level = level <= LVL_MIN ? 0 : (level >= LVL_MAX ? LVL_MAX : level);
    if((level / 2 / CHANNELS) > 1) SET_LED_ON();
    else SET_LED_OFF();
    pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, (int)(level / 2 / CHANNELS * LVL_MAX));
    wv->loc->t += wv->sleep_us;
    ++wv->loc->i;
    return;
}

void dstry_wave(Wave *wv) { return; }
