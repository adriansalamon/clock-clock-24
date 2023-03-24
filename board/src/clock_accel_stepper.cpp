#include "clock_accel_stepper.h"
#include "clock_state.h"


ClockAccelStepper::ClockAccelStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, ShiftRegister74HC595<1> *sr)
    : AccelStepper(interface, pin1, pin2) {
    _sr = sr;
};

void ClockAccelStepper::enableOutputs() {
    pinMode(_pin[0], OUTPUT);
}

void ClockAccelStepper::setOutputPins(uint8_t mask) {
    _step = (mask & (1 << 0)) ? (HIGH ^ _pinInverted[0]) : (LOW ^ _pinInverted[0]);
    if (_pin[0] < 8) {
        PORTD = (PORTD & ~(1 << _pin[0])) | (_step << _pin[0]);
    } else {
        PORTB = (PORTB & ~(1 << (_pin[0] - 8))) | (_step << (_pin[0] - 8));
    }
      
    _dir = (mask & (1 << 1)) ? (HIGH ^ _pinInverted[1]) : (LOW ^ _pinInverted[1]);
    if (_sr->get(_pin[1]) != _dir)
    {
        _sr->set(_pin[1], _dir);
    }
}

void ClockAccelStepper::setReverse(bool reverse) {
    _reverse = reverse;
}

int ClockAccelStepper::calcAngleClockwise(int angle_1, int angle_2) {
    int delta = (angle_2 - angle_1) % 360;
    return (delta <= 0) ? -delta : 360 - delta;
}

int ClockAccelStepper::calcAngleCounterClockwise(int angle_1, int angle_2) {
    int delta = (angle_2 - angle_1) % 360;
    return (delta >= 0) ? delta : 360 + delta;
}

void ClockAccelStepper::moveToAngle(int angle, int direction) {
    int delta;

    if (direction == CLOCKWISE) {
        delta = calcAngleClockwise(_current_angle, angle);
    } else if (direction == COUNTERCLOCKWISE) {
        delta = calcAngleCounterClockwise(_current_angle, angle);
    }
    
    _current_angle = angle;
    int steps = delta * 12; // Microstepping 12x
    if (direction == COUNTERCLOCKWISE) {
        steps = -steps; 
    }

    move(steps);    
}

