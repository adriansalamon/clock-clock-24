#ifndef CLOCK_ACCEL_STEPPER_H
#define CLOCK_ACCEL_STEPPER_H

#include <AccelStepper.h>
#include <ShiftRegister74HC595.h>
#include "board_config.h"

class ClockAccelStepper : public AccelStepper
{
private:
    /// Whether the _pins is inverted or not
    /// The shift register to use
    ShiftRegister74HC595<1> *_sr;
    uint8_t _dir;
    uint8_t _step;
    t_mag_pin _mag_pin;
    uint16_t _current_angle;
    bool _reverse;
    bool _zeroing;

    bool _mag_active();

public:
    explicit ClockAccelStepper(uint8_t interface = AccelStepper::DRIVER, uint8_t pin1 = 2, uint8_t pin2 = 3, 
                                t_mag_pin mag_pin = mag_pin{0, false}, ShiftRegister74HC595<1> *sr = NULL);

    void enableOutputs() override;

    void setReverse(bool reverse);

    void moveToAngle(int angle, int direction);

    int calcAngleClockwise(int angle_1, int angle_2);

    int calcAngleCounterClockwise(int angle_1, int angle_2);

    bool isZeroing();

    void zero();

protected:
    void setOutputPins(uint8_t mask) override;
};

#endif // CLOCK_ACCEL_STEPPER_H