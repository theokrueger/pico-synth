#ifndef WAVES_H
#define WAVES_H

#include "buttons.h"

#define LVL_MAX 4096

enum WaveTypes {
    SineWave,
    SquareWave,
    SawWave,
    TriangleWave
};

typedef struct {
    uint slice_num;
} WV_LOC;

typedef struct {
    int32_t sleep_us;
    WV_LOC *loc;
    int mult;
    int type;
    uint64_t time;
    uint64_t start;
} Wave;

Wave *setup_wave();
void update_wave(Wave *wv, Input *inp);


#endif