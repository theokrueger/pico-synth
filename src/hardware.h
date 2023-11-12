#ifndef HARDWARE_MAP
#define HARDWARE_MAP

// Joystick.
#define JSX_GPIO 26
#define JSX_ADC 1
#define JSY_GPIO 26
#define JSY_ADC 0
#define JSB_GPIO 22


// Fret buttons.
#define BUTTON_C 4
#define BUTTON_CS 5
#define BUTTON_D 6
#define BUTTON_DS 7
#define BUTTON_E 8
#define BUTTON_F 9
#define BUTTON_FS 10
#define BUTTON_G 11
#define BUTTON_GS 12
#define BUTTON_A 13
#define BUTTON_AS 14
#define BUTTON_B 15

// Masks for fret buttons
#define MASK_BUTTON_C 1
#define MASK_BUTTON_CS 2
#define MASK_BUTTON_D 4
#define MASK_BUTTON_DS 8
#define MASK_BUTTON_E 16
#define MASK_BUTTON_F 32
#define MASK_BUTTON_FS 64
#define MASK_BUTTON_G 128
#define MASK_BUTTON_GS 256
#define MASK_BUTTON_A 512
#define MASK_BUTTON_AS 1024
#define MASK_BUTTON_B 2048

// Freqs
#define FREQ_C 261.6256f 
#define FREQ_CS 277.1826f
#define FREQ_D 293.6648f 
#define FREQ_DS 311.1270f
#define FREQ_E 329.6276f
#define FREQ_F 349.2282f
#define FREQ_FS 369.9944f
#define FREQ_G 391.9954f
#define FREQ_GS 415.302f
#define FREQ_A 440.0f
#define FREQ_AS 466.164f
#define FREQ_B 493.883f

#endif