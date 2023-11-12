#include "buttons.h"
#include "pico/stdlib.h"
#include <stdlib.h>

#define COOLDOWN 500
#define ADC_FLOAT 1.0f * adc_read() / (0xFFF)
Input* setup_input()
{
        // defs
        Input *inp = (Input*) malloc(sizeof(Input));
        inp->jsb = false;
        inp->jsx = 0.0f;
	inp->jsy = 0.0f;

	// button

        // adc
        adc_init();
        adc_gpio_init(JSX_GPIO);
	adc_gpio_init(JSY_GPIO);

	return inp;
}

void get_inputs(Input *inp, int t_ms)
{
	/* JOYSTICK */
	// joystick button
	if (inp->jsb_cd + COOLDOWN < t_ms) {
		inp->jsb_cd = 0;
	}
        // joystick x
        adc_select_input(JSX_ADC);
        inp->jsx = ADC_FLOAT;

	// joystick y
	adc_select_input(JSY_ADC);
	inp->jsy = ADC_FLOAT;

	return;
}

void update_data(Input *inp)
{
	// jsx -> freq
	//wv->hz = inp->jsx * LVL_MAX;
	return;
}

void upd_input(Input *inp, int t_ms)
{
	get_inputs(inp, t_ms);
	update_data(inp);
	return;
}
