#include "waves.h"
#include "hardware.h"

#define M_PI 3.14159265358979323846
#define CHANNELS 4
const float conversion_factor = 3.3f / (1 << 12);

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/pwm.h"
#include "led.h"
#include "pico/stdlib.h"

#define AUD_OUT 0

Wave *setup_wave() {
    Wave *wv = (Wave *) malloc(sizeof(Wave));
    stdio_init_all();
    wv->start = time_us_64();
    wv->mult = 8;
    wv->loc = (WV_LOC *) malloc(sizeof(WV_LOC));
    wv->type = SawWave;
    wv->min_read = 0;
    wv->mod = 1;
    // gpio setup
    wv->loc->slice_num = pwm_gpio_to_slice_num(AUD_OUT);
    gpio_set_function(AUD_OUT, GPIO_FUNC_PWM);
    pwm_set_wrap(wv->loc->slice_num, LVL_MAX - 1);
    pwm_set_enabled(wv->loc->slice_num, true);
    return wv;
}

// Returns a value between 0 and 1.0 that denotes the amp of the wave
double get_level(Wave *wv, double newhz) {
    newhz *= wv->mult * wv->mod;
    // effective_time stores
    double effective_time = (newhz * (wv->time - wv->start) / 1000000);
    effective_time -= (int) effective_time;
    switch (wv->type) {
        case SineWave: {
            double c = cos(M_PI * effective_time);
            return c * c;
        }
        case SquareWave:
            return effective_time < 0.5f;
        case SawWave:
            return effective_time;
        case TriangleWave:
            return 2 * fabs(0.5f - effective_time);
        default:
            // error
            SET_LED_ON();
            break;
    };
    return 0;
}

void update_wave(Wave *wv, Input *inp) {
    if (inp->signal) {
        switch (wv->type) {
            case SineWave:
                wv->type = SquareWave;
                break;
            case SquareWave:
                wv->type = SawWave;
                break;
            case SawWave:
                wv->type = TriangleWave;
                break;
            case TriangleWave:
                wv->type = SineWave;
                break;
        }
    }
    double level = 0;
    if (inp->fret_state) {
        SET_LED_ON();
        wv->time = time_us_64();
        if (wv->time - wv->min_read > 100000) {
            uint16_t val = adc_read();
            printf("%llu %hu %f\n", wv->min_read - wv->time, val, exp2f((val - 2048.0f) / 2048.0f));
            wv->mod = exp2f((val - 2048.0f) / 2048.0f);
            wv->min_read = wv->time;
        }

        if (inp->fret_state & (1 << 4)) level += get_level(wv, FREQ_C);
        if (inp->fret_state & (1 << 8)) level += get_level(wv, FREQ_CS);
        if (inp->fret_state & (1 << 12)) level += get_level(wv, FREQ_D);
        if (inp->fret_state & (1 << 11)) level += get_level(wv, FREQ_DS);
        if (inp->fret_state & (1 << 13)) level += get_level(wv, FREQ_E);
        if (inp->fret_state & (1 << 10)) level += get_level(wv, FREQ_F);
        if (inp->fret_state & (1 << 6)) level += get_level(wv, FREQ_FS);
        if (inp->fret_state & (1 << 5)) level += get_level(wv, FREQ_G);
        if (inp->fret_state & (1 << 7)) level += get_level(wv, FREQ_GS);
        if (inp->fret_state & (1 << 14)) level += get_level(wv, FREQ_A);
        if (inp->fret_state & (1 << 15)) level += get_level(wv, FREQ_AS);
        if (inp->fret_state & (1 << 9)) level += get_level(wv, FREQ_B);
        level /= CHANNELS;
        pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, (int) (level * LVL_MAX));
    } else {
        SET_LED_OFF();
    }
    return;
}

void dstry_wave(Wave *wv) { return; }
