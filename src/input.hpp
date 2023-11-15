#ifndef INPUT_H
#define INPUT_H

#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware.h"

// buttons store their state next update, pots always store
namespace PicoSynth {
    class GPIOHandle {
        public:
            GPIOHandle();
            void Update();
            bool GetAnyFretPressed();
            bool GetFretPressed(uint32_t fret_mask);
            bool GetJoystickButtonPressed();
            float GetJoystickXRaw();
            float GetJoystickYRaw();
            float GetJoystickXCentered();
            float GetJoystickYCentered();
            void SetDebugLED(bool status);
        private:
            float m_JoystickX = 0.0f;
            float m_JoystickY = 0.0f;
            uint32_t m_FretState = 0;
            bool m_JoystickButton = false;
    };
};

#endif