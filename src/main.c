#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "buttons.h"
#include "waves.h"
#include "led.h"
#include <time.h>

int main() {
	//setup
	setup_led();
	Input *input = setup_input();
	Wave *wave = setup_wave();
	//loop
	while(1) {
	        uint64_t start = time_us_64();
		upd_input(input);
		upd_wave(wave);

		uint64_t diff = time_us_64() - start;
		sleep_us(wave->sleep_us - diff);
	}
	dstry_wave(wave);
}
