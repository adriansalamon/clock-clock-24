#include "board.h"

ShiftRegister74HC595<1> sr(10, 1, 0);

ClockAccelStepper _motors[8] = {
    ClockAccelStepper(AccelStepper::DRIVER, A1_STEP, A1_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, B1_STEP, B1_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, A2_STEP, A2_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, B2_STEP, B2_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, A3_STEP, A3_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, B3_STEP, B3_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, A4_STEP, A4_DIR, &sr),
    ClockAccelStepper(AccelStepper::DRIVER, B4_STEP, B4_DIR, &sr)};

static int clip_angle(int angle)
{
    angle = angle % 360;
    return angle < 0 ? angle + 360 : angle;
}

void board_begin()
{
    pinMode(RESET, OUTPUT);
    digitalWrite(RESET, HIGH);

    for (int i = 0; i < 8; i++)
    {
        _motors[i].setMaxSpeed(4000.0);
        _motors[i].setAcceleration(1000.0);
    }
}

void board_loop()
{
    for (int i = 0; i < 8; i++)
        _motors[i].run();
}

void set_clock(int index, t_clock state)
{
    int angle_h = clip_angle(state.angle_h);
    _motors[index * 2].setMaxSpeed(state.speed_h);
    _motors[index * 2].setAcceleration(state.accel_h);
    _motors[index * 2].moveToAngle(angle_h, state.direction_h);

    int angle_m = clip_angle(state.angle_m);
    _motors[index * 2 + 1].setMaxSpeed(state.speed_m);
    _motors[index * 2 + 1].setAcceleration(state.accel_m);
    _motors[index * 2 + 1].moveToAngle(angle_m, state.direction_m);
}