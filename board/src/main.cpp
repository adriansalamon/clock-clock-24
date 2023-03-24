/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Wire.h>
#include "i2c.h"
#include "board.h"
#include "clock_accel_stepper.h"

#define I2C_ADDR 0x10

const t_clock default_clock = {0, 0, 0, 0, 0, 0, 0, 0};

t_full_clock target_clocks;
t_full_clock current_clocks;
int current_clock = 0;

void receiveEvent(int howMany)
{
    if (howMany >= sizeof(t_half_clock))
    {
        t_half_clock tmp_state;
        I2C_readAnything(tmp_state);

        for (uint8_t i = 0; i < 2; i++)
        {
            target_clocks.clocks[current_clock + i] = tmp_state.clocks[i];
            target_clocks.change_counter[current_clock + i] = tmp_state.change_counter[i];
        }

        current_clock += 2;
        if (current_clock >= NUM_CLOCKS)
            current_clock = 0;
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    board_begin();

    target_clocks = {{default_clock, default_clock, default_clock, default_clock}, {0, 0, 0, 0}};
    current_clocks = {{default_clock, default_clock, default_clock, default_clock}, {0, 0, 0, 0}};

    Wire.begin(I2C_ADDR);
    Wire.onReceive(receiveEvent);

    for (uint8_t i = 0; i < NUM_CLOCKS; i++)
        set_clock(i, current_clocks.clocks[i]);
}

void loop()
{
    board_loop();

    for (uint8_t i = 0; i < NUM_CLOCKS; i++)
    {
        if (current_clocks.change_counter[i] != target_clocks.change_counter[i])
        {
            current_clocks.clocks[i] = target_clocks.clocks[i];
            current_clocks.change_counter[i] = target_clocks.change_counter[i];

            set_clock(i, current_clocks.clocks[i]);
        }
    }
}
