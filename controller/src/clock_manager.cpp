#include "clock_manager.h"

int I2C_ADDR[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

ClockManager clock_manager = ClockManager(I2C_ADDR);

const t_clock default_clock = {
    .angle_h = 0,
    .angle_m = 0,
    .speed_h = 2000,
    .speed_m = 2000,
    .accel_h = 500,
    .accel_m = 500,
    .direction_h = CLOCKWISE,
    .direction_m = CLOCKWISE};

ClockManager::ClockManager(int board_addrs[NUM_CLOCKS])
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        _board_addrs[i] = board_addrs[i];
    }
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j] = default_clock;
            _boards[i].change_counter[j] = 1;
        }
    }
}

void ClockManager::setHourSpeed(uint16_t speed)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].speed_h = speed;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setMinuteSpeed(uint16_t speed)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].speed_m = speed;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setHourAccel(uint16_t accel)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].accel_h = accel;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setMinuteAccel(uint16_t accel)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].accel_m = accel;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setHourDirection(uint8_t direction)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].direction_h = direction;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setMinuteDirection(uint8_t direction)
{
    for (int i = 0; i < NUM_CLOCKS; i++)
    {
        for (int j = 0; j < NUM_CLOCKS_PER_BOARD; j++)
        {
            _boards[i].clocks[j].direction_m = direction;
            _boards[i].change_counter[j]++;
        }
    }
}

void ClockManager::setClock(t_clock clock, int board, int clock_num)
{
    _boards[board].clocks[clock_num] = clock;
    _boards[board].change_counter[clock_num]++;
}

void ClockManager::setHalfDigit(int index, t_half_digit digit)
{
    if (index < 0 || index > 7)
        return;

    for (int i = 0; i < 3; i++)
    {
        if (index < 4)
        {
            _boards[i].clocks[index].angle_h = digit.lite_clock[i].angle_h;
            _boards[i].clocks[index].angle_m = digit.lite_clock[i].angle_m;
            _boards[i].change_counter[index]++;
        }
        else if (index < 8)
        {
            _boards[i + 3].clocks[index - 4].angle_h = digit.lite_clock[i].angle_h;
            _boards[i + 3].clocks[index - 4].angle_m = digit.lite_clock[i].angle_m;
            _boards[i + 3].change_counter[index - 4]++;
        }
    }
}

void ClockManager::setDigit(int index, t_digit digit)
{
    setHalfDigit(index * 2, get_left_half_digit(digit));
    setHalfDigit((index * 2) + 1, get_right_half_digit(digit));
}

void ClockManager::setWholeClock(t_full_digits digits)
{
    for (int i = 0; i < 4; i++)
    {
        setDigit(i, digits.digits[i]);
    }
}

void ClockManager::sendFullClock(int board)
{
    for (int i = 0; i < 2; i++)
    {
        t_half_clock to_send;
        to_send.clocks[0] = _boards[board].clocks[i * 2];
        to_send.clocks[1] = _boards[board].clocks[(i * 2) + 1];
        to_send.change_counter[0] = _boards[board].change_counter[i * 2];
        to_send.change_counter[1] = _boards[board].change_counter[(i * 2) + 1];

        Wire.beginTransmission(_board_addrs[board]);
        I2C_writeAnything(to_send);
        Wire.endTransmission();
    }
}

void ClockManager::sendFullClocks()
{
    for (int i = 0; i < NUM_CLOCKS; i++)
        sendFullClock(i);
}

void ClockManager::sendDigit(int index)
{
    for (int i = 0; i < 3; i++)
    {
        if (index <= 2)
            sendFullClock(i);
        else if (index <= 4)
            sendFullClock(i + 3);
    }
}

void ClockManager::sendHalfDigit(int index)
{
    for (int i = 0; i < 3; i++)
    {
        if (index <= 3)
            sendFullClock(i);
        else if (index <= 6)
            sendFullClock(i + 3);
    }
}

void ClockManager::setTime(int hour, int minute)
{
    t_full_digits digits = digits_from_number(hour * 100 + minute);
    setWholeClock(digits);
}

t_digit get_digit(int number)
{
    return digits[number];
}

t_half_digit get_left_half_digit(t_digit digit)
{
    t_half_digit half_digit;
    for (int i = 0; i < 3; i++)
        half_digit.lite_clock[i] = digit.lite_clock[i];
    return half_digit;
}

t_half_digit get_right_half_digit(t_digit digit)
{
    t_half_digit half_digit;
    for (int i = 0; i < 3; i++)
        half_digit.lite_clock[i] = digit.lite_clock[i + 3];
    return half_digit;
}

t_full_digits digits_from_number(int number) {

    if (number < 0 || number > 9999)
        return clock_null;

    t_full_digits full_digits;

    full_digits.digits[0] = get_digit(number / 1000);
    full_digits.digits[1] = get_digit((number / 100) % 10);
    full_digits.digits[2] = get_digit((number / 10) % 10);
    full_digits.digits[3] = get_digit(number % 10);

    return full_digits;
}