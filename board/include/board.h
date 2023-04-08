#ifndef BOARD_H
#define BOARD_H

#include "clock_accel_stepper.h"
#include "clock_state.h"
#include "board_config.h"

#define NUM_CLOCKS 4
#define INIT_HANDS_ANGLE 270

void board_begin();

void board_loop();

bool clock_is_running(int index);

void set_clock(int index, t_clock state);

void zero_clock(int index);

#endif // BOARD_H