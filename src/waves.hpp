#ifndef WAVES_H
#define WAVES_H

#include "input.hpp"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace PicoSynth {
    enum WaveTypes {
        SineWave,
        SquareWave,
        SawWave,
        TriangleWave
    };

    class Wave {
        public:
            Wave(GPIOHandle *handler);
            void Initialize();
            void Update();
        private:
            double CalculateLevel(double new_frequency, double modulation);
            WaveTypes m_WaveType;
            int32_t m_Sleep;
            uint m_SliceIndex;
            int m_Multiplier;
            uint64_t m_WaveTime;
            uint64_t m_WaveStart;
            GPIOHandle *m_InputHandler;
    };
};


#endif