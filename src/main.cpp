#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "waves.hpp"
#include "input.hpp"
#include <time.h>

int main() {
	stdio_init_all();
	PicoSynth::GPIOHandle *g_InputHandle = new PicoSynth::GPIOHandle();
	PicoSynth::Wave *g_WaveHandle = new PicoSynth::Wave(g_InputHandle);
	g_WaveHandle->Initialize();
	for (;;) {
		g_InputHandle->Update();
		g_WaveHandle->Update();
	}
}
