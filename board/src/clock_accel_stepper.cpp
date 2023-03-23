#include "clock_accel_stepper.h"


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

