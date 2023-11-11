#pragma once

/*
enum WaveType {
	SquareWave,
	SineWave,
	SawWave,
};

typedef struct {
	uint freq; //hz
	uint amp; // idk
	uint wt; // wave type
	int32_t sample_rate;
	int32_t interval_us;
	struct repeating_timer timer;
} Wave;

Wave* setup_wave();
void upd_wave(Wave *wv);
void dstry_wave(Wave *wv);
float conv_hz_to_div(int hz);
*/
typedef struct {} Wave;
Wave* setup_wave();
void upd_wave(Wave *wv);
void dstry_wave(Wave *wv);
