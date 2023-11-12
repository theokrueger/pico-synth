#include "hardware/pwm.h"
#include <stdlib.h>
#include "waves.h"
#include "led.h"
#include "pico/stdlib.h"

const uint AUD_OUT= 0;
const uint LVL_MAX = 16001;
//const uint wrap
//const uint LVL_MIN

Wave* setup_wave() {
        Wave *wv = (Wave*) malloc(sizeof(Wave));
        stdio_init_all();

        // local use only (ugly)
        wv->loc = (WV_LOC*) malloc(sizeof(WV_LOC));
        wv->loc->sampling_rate = 44000;
        wv->sleep_us = 1000000 / wv->loc->sampling_rate;
        wv->loc->t = 0;
	// params we change
        wv->hz = 471;
	wv->type = SquareWave;

	// gpio setup
        wv->loc->slice_num = pwm_gpio_to_slice_num(AUD_OUT);
        gpio_set_function(AUD_OUT, GPIO_FUNC_PWM);
        pwm_set_wrap(wv->loc->slice_num, 0);
        pwm_set_enabled(wv->loc->slice_num, true);

        return wv;
}

void upd_wave(Wave *wv) {
/*
	switch (wv->type)
	{
	case SquareWave:
		
		break;
	case SawWave:
		break;
	default:
		// error
		SET_LED_ON();
		breakl
	};*/
	++wv->loc->t;
        if ((wv->loc->t * 2 * wv->hz / wv->loc->sampling_rate) % 2) {
                pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, 1);
        } else{
                pwm_set_chan_level(wv->loc->slice_num, PWM_CHAN_A, 0);
        }
        
        return;
}
void dstry_wave(Wave *wv) {
        return;
}
