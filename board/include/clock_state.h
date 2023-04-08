#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

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
    ZERO // Zero the clock
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

#endif // CLOCK_STATE_H