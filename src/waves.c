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
    wv->mult = 16;
    // local use only (ugly)
    wv->loc = (WV_LOC *)malloc(sizeof(WV_LOC));
    wv->loc->sampling_rate = 44000;
    wv->sleep_us = 1000 * 1000 / wv->loc->sampling_rate;
    wv->loc->t = 0;
    wv->loc->i = 0;
    // params we change
//     wv->hz = (int)(840.0f * pow(HALFSTEP, 3));  // calibrate per speaker for some reason????
    wv->type = SineWave;

    // gpio setup
    wv->loc->slice_num = pwm_gpio_to_slice_num(AUD_OUT);
    gpio_set_function(AUD_OUT, GPIO_FUNC_PWM);
    pwm_set_wrap(wv->loc->slice_num, WRAP);
    pwm_set_enabled(wv->loc->slice_num, true);
    return wv;
}

// Returns a value between 0 and 2.0 that denotes the amp of the wave
float get_level(Wave *wv, float newhz){
        switch (wv->type) {
        case SineWave:
            return 1 - cosf(2 * M_PI * newhz * wv->mult * wv->loc->i /
                              wv->loc->sampling_rate) ;
        case SquareWave:
                return 2 * ((int)(wv->loc->i * 2*  newhz / wv->loc->sampling_rate) % 2);  
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
    printf("%f\n", inp->jsx);
    if (inp->jsx) {// Place holder condition
        if(inp->jsx < 0 && wv->mult > 1){
                wv->mult >>= 1;
        }else if(inp->jsx > 0 && wv->mult < 256){
                wv->mult <<= 1;
        }
    }
    if (inp->fret_state) {
        SET_LED_ON();
        if(inp->fret_state & MASK_BUTTON_C) level += get_level(wv, FREQ_C);
        if(inp->fret_state & MASK_BUTTON_CS) level += get_level(wv, FREQ_CS);
        if(inp->fret_state & MASK_BUTTON_D) level += get_level(wv, FREQ_D);
        if(inp->fret_state & MASK_BUTTON_DS) level += get_level(wv, FREQ_DS);
        if(inp->fret_state & MASK_BUTTON_E) level += get_level(wv, FREQ_E);
        if(inp->fret_state & MASK_BUTTON_F) level += get_level(wv, FREQ_F);
        if(inp->fret_state & MASK_BUTTON_FS) level += get_level(wv, FREQ_FS);
        if(inp->fret_state & MASK_BUTTON_G) level += get_level(wv, FREQ_G);
        if(inp->fret_state & MASK_BUTTON_GS) level += get_level(wv, FREQ_GS);
        if(inp->fret_state & MASK_BUTTON_A) level += get_level(wv, FREQ_A);
        if(inp->fret_state & MASK_BUTTON_AS) level += get_level(wv, FREQ_AS);
        if(inp->fret_state & MASK_BUTTON_B) level += get_level(wv, FREQ_B);
    } else{
        SET_LED_OFF();
    }

//     level = level <= LVL_MIN ? 0 : (level >= LVL_MAX ? LVL_MAX : level);
    pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, (int)(level /
                    2 / CHANNELS * LVL_MAX));
    wv->loc->t += wv->sleep_us;
    ++wv->loc->i;
    return;
}

void dstry_wave(Wave *wv) { return; }
