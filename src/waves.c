#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "waves.h"
#include <math.h>
#include <stdlib.h>

#define SPEAKER_PWM 0

Wave* setup_wave()
{
	// wv setup
	Wave *wv = (Wave*) malloc(sizeof(Wave));
	wv->freq = 300;
	wv->amp = 0; // TODO
	wv->wt = SquareWave;

	return wv;
}
void upd_wave(Wave *wv)
{
	return;
}


float conv_hz_to_div(int hz) {
	return (float)(pow(10,8)*1.25/(4096*16*hz));
}
