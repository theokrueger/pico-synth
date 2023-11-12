#include "hardware/pwm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waves.h"
#include "led.h"
#include "pico/stdlib.h"

#define AUD_OUT 0

Wave* setup_wave() {
        Wave *wv = (Wave*) malloc(sizeof(Wave));
        stdio_init_all();

        // local use only (ugly)
        wv->loc = (WV_LOC*) malloc(sizeof(WV_LOC));
        wv->loc->sampling_rate = 44000;
        wv->sleep_us = 1000 * 1000 / wv->loc->sampling_rate;
        wv->loc->t = 0;
	wv->loc->i = 0;
        // params we change
        wv->hz = (int)(840.0f * pow(HALFSTEP, 3)); // calibrate per speaker for some reason????
        wv->type = SineWave;

        // gpio setup
        wv->loc->slice_num = pwm_gpio_to_slice_num(AUD_OUT);
        gpio_set_function(AUD_OUT, GPIO_FUNC_PWM);
        pwm_set_wrap(wv->loc->slice_num, WRAP);
        pwm_set_enabled(wv->loc->slice_num, true);

        return wv;
}

void upd_wave(Wave *wv, Input *inp) {
        double level = 0;
	int newhz = wv->hz;
	//newhz += (inp->jsx - (0xFFF >> 1)) * 2 * 1000;
	printf("%f\n", inp->jsx);
        switch (wv->type)
        {
        case SineWave:
                level = (1 + sinf(2*M_PI*newhz*wv->loc->i/wv->loc->sampling_rate))/2*LVL_MAX;
		break;
        case SquareWave:
//		level = sleep_us
                break;
        case SawWave:
                break;
        default:
                // error
                SET_LED_ON();
                break;
        };
        level = level <= LVL_MIN ? 0 : (level >= LVL_MAX ? LVL_MAX : level );
	pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, (int)level);
	wv->loc->t += wv->sleep_us;
	++wv->loc->i;
        return;
}

void dstry_wave(Wave *wv) {
        return;
}
