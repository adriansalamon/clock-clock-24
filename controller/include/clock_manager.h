#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <Arduino.h>
#include <Wire.h>

#include "clock_state.h"
#include "i2c.h"
#include "digits.h"

// Boards should be laid out in order:
//
//  |-------------------|
//  | Board 1 | Board 4 |
//  | Board 2 | Board 5 |
//  | Board 3 | Board 6 |
//  |-------------------|
//

class ClockManager {
    private:
        int _board_addrs[NUM_CLOCKS];
        t_full_clock _boards[NUM_CLOCKS];


    public:
        ClockManager(int board_addrs[NUM_CLOCKS]);
        
        void setHourSpeed(uint16_t speed);
        void setMinuteSpeed(uint16_t speed);
        void setHourAccel(uint16_t accel);
        void setMinuteAccel(uint16_t accel);
        void setHourDirection(uint8_t direction);
        void setMinuteDirection(uint8_t direction);

        /**
         * @brief Sets the clock at the given index, and increments the change counter
         * 
         * @param clock The clock to set
         * @param board The index of the board to set the clock on (0 <= board <= 6)
         * @param clock_num The index of the clock on the board (0 <= clock_num <= 4)
         */
        void setClock(t_clock clock, int board, int clock_num);

        /**
         * @brief Sets the digit at the given index, and increments the change counter
         * 
         * @param index The index of the digit (0 <= index <= 4)
         * @param digit The digit to set
         */
        void setDigit(int index, t_digit digit);
        

        void setWholeClock(t_full_digits digits);

        /**
         * @brief Sets the half digit at the given index, and increments the change counter
         * 
         * @param index The index of the half digit (0 <= index <= 8)
         * @param digit The half digit to set
         */
        void setHalfDigit(int index, t_half_digit digit);

        /**
         * @brief Sends the full clock to the given board
         * 
         * @param board The index of the board to send the clock to (0 <= board <= 6)
         */
        void sendFullClock(int board);

        /**
         * @brief Sends the full clocks to all boards
         */
        void sendFullClocks();

        /**
         * @brief Sends the digit to boards
         * 
         * @param board The index of the digit (0 <= index <= 4)
         */
        void sendDigit(int index);

        /**
         * @brief Sends the half digit to boards
         * 
         * @param board The index of the half digit (0 <= index <= 8)
         */
        void sendHalfDigit(int index);

        /**
         * @brief Sets the time on the clock
         * 
         * @param hour A number between 0 and 23
         * @param minute A number between 0 and 59
         */
        void setTime(int hour, int minute);
};

t_half_digit get_left_half_digit(t_digit digit);
t_half_digit get_right_half_digit(t_digit digit);
t_digit get_digit(int number);

t_full_digits digits_from_number(int number);

extern ClockManager clock_manager;

#endif // CLOCK_MANAGER_H