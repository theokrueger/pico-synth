#pragma once

#include "hardware/gpio.h"
#include "hardware/adc.h"

#define POT1PIN_GPIO 26
#define POT1PIN_ADC 0

// from https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf pg.82
#define ADC_VREF 3.3
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1))

// buttons store their state next update, pots always store
typedef struct {
	bool button1;
	uint pot1;
} Input;

Input* setup_input();
void upd_input(Input *inp);
