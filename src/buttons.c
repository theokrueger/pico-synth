#include "buttons.h"
#include "pico/stdlib.h"
#include <stdlib.h>

Input* setup_input()
{
	// defs
	Input *inp = (Input*) malloc(sizeof(Input));
	inp->button1 = false;
	inp->pot1 = 0;

	// adc
	adc_init();
	adc_gpio_init(POT1PIN_GPIO);
}

void upd_input(Input *inp)
{
	// buttons
	// TODO

	// potentiometers
	adc_select_input(POT1PIN_ADC);
	inp->pot1 = adc_read() * ADC_CONVERT;
}
