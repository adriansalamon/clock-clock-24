#include "clock_accel_stepper.h"
#include "clock_state.h"

ClockAccelStepper::ClockAccelStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, t_mag_pin mag_pin, ShiftRegister74HC595<1> *sr)
    : AccelStepper(interface, pin1, pin2)
{
    _sr = sr;
    _mag_pin = mag_pin;
    pinMode(_mag_pin.pin, INPUT_PULLUP);
};

void ClockAccelStepper::enableOutputs()
{
    pinMode(_pin[0], OUTPUT);
}

void ClockAccelStepper::setOutputPins(uint8_t mask)
{
    // Set step pin using port registers for speed
    _step = (mask & (1 << 0)) ? (HIGH ^ _pinInverted[0]) : (LOW ^ _pinInverted[0]);
    if (_pin[0] < 8)
        PORTD = (PORTD & ~(1 << _pin[0])) | (_step << _pin[0]);
    else
        PORTB = (PORTB & ~(1 << (_pin[0] - 8))) | (_step << (_pin[0] - 8));

    // Sed the direction pin using the shift register. We only need to do this if the direction has changed.
    _dir = (mask & (1 << 1)) ? (HIGH ^ _pinInverted[1]) : (LOW ^ _pinInverted[1]);
    if (_sr->get(_pin[1]) != _dir)
        _sr->set(_pin[1], _dir);
}

void ClockAccelStepper::setReverse(bool reverse)
{
    _reverse = reverse;
}

int ClockAccelStepper::calcAngleClockwise(int angle_1, int angle_2)
{
    int delta = (angle_2 - angle_1) % 360;
    return (delta < 0) ? 360 + delta : delta;
}

int ClockAccelStepper::calcAngleCounterClockwise(int angle_1, int angle_2)
{
    int delta = (angle_1 - angle_2) % 360;
    return (delta < 0) ? 360 + delta : delta;
}

void ClockAccelStepper::moveToAngle(int angle, int direction)
{
    int delta;
    uint8_t multiplier = 0;

    if (direction <= CLOCKWISE3)
    {
        delta = calcAngleClockwise(_current_angle, angle);
        multiplier = direction;
    }
    else if (direction <= COUNTERCLOCKWISE3)
    {
        delta = calcAngleCounterClockwise(_current_angle, angle);
        multiplier = direction - COUNTERCLOCKWISE;
    }
    else if (direction == CLOSEST)
    {
        int delta_cw = calcAngleClockwise(_current_angle, angle);
        int delta_ccw = calcAngleCounterClockwise(_current_angle, angle);
        direction = (delta_cw < delta_ccw) ? CLOCKWISE : COUNTERCLOCKWISE;
        delta = (delta_cw < delta_ccw) ? delta_cw : delta_ccw;
    }
    else if (direction == ZERO)
    {
        zero();
        return;
    }

    _current_angle = angle;
    int steps = delta * 12; // Microstepping 12x

    if (direction <= CLOCKWISE3)
        steps = steps + (N_STEPS * multiplier);
    else if (direction <= COUNTERCLOCKWISE3)
        steps = -1 * (steps + (N_STEPS * multiplier));

    move(steps * (_reverse ? -1 : 1));
}

void ClockAccelStepper::zero()
{
    _zeroing = true;

    while (_zeroing)
    {

        while (_mag_active())
        {
            move(-200);
            run();
        }

        while (!_mag_active())
        {
            move(200);
            run();
        }
        int pos = currentPosition();

        while (_mag_active())
        {
            move(200);
            run();
        }

        while (!_mag_active())
        {
            move(-200);
            run();
        }
        int end_pos = currentPosition();

        runToNewPosition((pos + end_pos) / 2);

#if INVERTED
        _current_angle = 270;
#else
        _current_angle = 90;
#endif

        _zeroing = false;
    }
}

bool ClockAccelStepper::_mag_active()
{
    if (_mag_pin.analog)
        return analogRead(_mag_pin.pin) < MAG_THRESHOLD;
    else
        return digitalRead(_mag_pin.pin) == LOW;
}

bool ClockAccelStepper::isZeroing()
{
    return _zeroing;
}