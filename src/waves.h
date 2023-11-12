#ifndef WAVES_H
#define WAVES_H

#include "buttons.h"

#define WRAP 1000
#define LVL_MAX WRAP + 1
#define LVL_MIN 0
#define HALFSTEP 1.05946309436

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
    int mult;
    int type;
} Wave;

Wave *setup_wave();
void update_wave(Wave *wv, Input *inp);
void dstry_wave(Wave *wv);

#endif