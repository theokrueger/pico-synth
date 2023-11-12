#pragma once

enum WaveTypes {
	SineWave,
	SquareWave,
	SawWave,
};

typedef struct {
        int32_t sampling_rate;
	uint64_t t;
	uint64_t i;
	uint slice_num;
} WV_LOC;

typedef struct {
	int32_t sleep_us;
        WV_LOC *loc;
	int hz;
	int type;
} Wave;

Wave* setup_wave();
void upd_wave(Wave *wv);
void dstry_wave(Wave *wv);

