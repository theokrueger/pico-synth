#include "led.h"

#include "pico/stdlib.h"

const uint LED_PIN = 25;

void setup_led() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void SET_LED_ON() { 
	gpio_put(LED_PIN, 1); 
}

void SET_LED_OFF() { 
	gpio_put(LED_PIN, 0); 
}
