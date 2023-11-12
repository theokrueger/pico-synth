#pragma once

#include "hardware/gpio.h"
#include "hardware/adc.h"

#define JSX_GPIO 26
#define JSX_ADC 1
#define JSY_GPIO 26
#define JSY_ADC 0
#define JSB_GPIO 22

// buttons store their state next update, pots always store
typedef struct {
	bool jsb;
	uint16_t jsb_cd;
	float jsx;
	float jsy;
} Input;

Input* setup_input();
void upd_input(Input *inp, int t_ms);
