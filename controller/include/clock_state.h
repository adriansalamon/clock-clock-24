#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

#include <Arduino.h>

// SHARED STATE WITH BOARDS

enum directions {
    CLOCKWISE,
    CLOCKWISE1, // One extra revolution
    CLOCKWISE2, // Two extra revolutions
    CLOCKWISE3, // Three extra revolutions
    COUNTERCLOCKWISE,
    COUNTERCLOCKWISE1, // One extra revolution
    COUNTERCLOCKWISE2, // Two extra revolutions
    COUNTERCLOCKWISE3, // Three extra revolutions
    CLOSEST, // Closest direction
    ZERO // Calibrate to zero
};

typedef struct clock_state {
    uint16_t angle_h;
    uint16_t angle_m;
    uint16_t speed_h;
    uint16_t speed_m;
    uint16_t accel_h;
    uint16_t accel_m;
    uint8_t direction_h;
    uint8_t direction_m;
} t_clock;

typedef struct half_clock {
    t_clock clocks[2];
    uint16_t change_counter[2];
} t_half_clock;

typedef struct clock {
  t_clock clocks[4];
  uint16_t change_counter[4];
} t_full_clock;

// CONTROLLER STATE ONLY

#define NUM_CLOCKS 6
#define NUM_CLOCKS_PER_BOARD 4

typedef struct lite_clock {
    uint32_t angle_h;
    uint32_t angle_m;
} t_lite_clock;

typedef struct half_digit {
    t_lite_clock lite_clock[3];
} t_half_digit;

typedef struct digit {
    t_lite_clock lite_clock[6]; // 6 clocks per digit   
} t_digit;

typedef struct full_digits {
    t_digit digits[4];
} t_full_digits;

#endif // CLOCK_STATE_H