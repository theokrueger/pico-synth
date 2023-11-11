#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include "waves.h"

const int32_t sampling_rate = 44000;
const int32_t interval_us = 1000000 / sampling_rate;
int counter = 0;
uint slice_num;
const int hz = 471;

bool repeating_timer_callback(struct repeating_timer *t) {
	counter++;
	if ((counter * 2 * hz / sampling_rate) % 2) {
		pwm_set_chan_level(slice_num, PWM_CHAN_A, 8000);
	} else{
		pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
	}
	return true;
}

Wave* setup_wave() {
	stdio_init_all();
	slice_num = pwm_gpio_to_slice_num(0);
	gpio_set_function(0, GPIO_FUNC_PWM);
	pwm_set_wrap(slice_num, 16000);
	pwm_set_enabled(slice_num, true);


	// Create a repeating timer that calls repeating_timer_callback.
	// If the delay is > 0 then this is the delay between the previous callback ending and the next starting.
	// If the delay is negative (see below) then the next call to the callback will be exactly 500ms after the
	// start of the call to the last callback
	struct repeating_timer timer;
	add_repeating_timer_us(-interval_us, repeating_timer_callback, NULL, &timer);
	sleep_ms(10000);
	bool cancelled = cancel_repeating_timer(&timer);
	pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
	sleep_ms(2000);
	return (Wave*) malloc(sizeof(Wave));
}

void upd_wave(Wave *wv) { return; }
void dstry_wave(Wave *wv) { return; }

/*
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "waves.h"
#include <math.h>
#include <stdlib.h>

#define SPEAKER_PWM 0

int counter = 0;
static int hz = 471;
const int32_t sample_rate = 44000;
const int32_t interval_us = 1000000 / sample_rate;
uint slice;

bool repeating_timer_callback(struct repeating_timer *t) {
    counter++;
    if ((counter * 2 * hz / sample_rate) % 2) {
        pwm_set_chan_level(slice, PWM_CHAN_A, 8000);
    } else{
        pwm_set_chan_level(slice, PWM_CHAN_A, SPEAKER_PWM);
    }
    return true;
}

Wave* setup_wave()
{
	// wv setup
	Wave *wv = (Wave*) malloc(sizeof(Wave));
	wv->freq = 471;
	wv->amp = 0; // TODO
	wv->wt = SquareWave;
	wv->sample_rate = 44000;
	wv->interval_us = 1000000 / sample_rate;
	wv->timer

	// gpio
	stdio_init_all();
	slice = pwm_gpio_to_slice_num(SPEAKER_PWM);
	gpio_set_function(SPEAKER_PWM, GPIO_FUNC_PWM);
	pwm_set_wrap(slice, 16000);
	pwm_set_enabled(slice, true);

	// start
	struct repeating_timer timer;
	add_repeating_timer_us(-interval_us, repeating_timer_callback, NULL, &(wv->timer));

	return wv;
}
void upd_wave(Wave *wv)
{
	// (updating settings would go here)
	return;
}

void dstry_wave(Wave *wv)
{
	cancel_repeating_timer(&(wv->timer));
	pwm_set_chan_level(slice, PWM_CHAN_A, SPEAKER_PWM);
	return;
}


float conv_hz_to_div(int hz) {
	return (float)(pow(10,8)*1.25/(4096*16*hz));
}
*/
