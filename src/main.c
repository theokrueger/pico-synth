// Output PWM signals on pins 0 and 1

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "buttons.h"
#include "waves.h"

int main() {
	//setup
	Input *input = setup_input();
	Wave *wave = setup_wave();
	//loop
	while(1) {
		upd_input(input);
		upd_wave(wave);
	}
}
