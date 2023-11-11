#pragma once

enum WaveType {
	SquareWave,
	SineWave,
	SawWave,
};

typedef struct {
	uint freq; //hz
	uint amp; // idk
	uint wt; // wave type
} Wave;

Wave* setup_wave();
void upd_wave(Wave *wv);
float conv_hz_to_div(int hz);
