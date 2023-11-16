#include "buttons.h"
#include "waves.h"
#include "led.h"
#include <stdio.h>

int main() {

    //setup
    setup_led();
    Input *input = setup_input();
    Wave *wave = setup_wave();
    //loop
    while (1) {
        update_input(input, 0); // approximate 1 second
        update_wave(wave, input);
    }
}
