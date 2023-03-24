#ifndef CLOCK_ACCEL_STEPPER_H
#define CLOCK_ACCEL_STEPPER_H

#include <AccelStepper.h>
#include <ShiftRegister74HC595.h>

class ClockAccelStepper : public AccelStepper
{
private:
    /// Whether the _pins is inverted or not
    /// The shift register to use
    ShiftRegister74HC595<1> *_sr;
    uint8_t _step;
    uint8_t _dir;
    uint8_t _current_angle;
    bool _reverse;

public:
    explicit ClockAccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, 
                                ShiftRegister74HC595<1> *sr = NULL);

    void enableOutputs() override;

    void moveToAngle(int angle, int direction);

    void setReverse(bool reverse);

    int calcAngleClockwise(int angle_1, int angle_2);

    int calcAngleCounterClockwise(int angle_1, int angle_2);

protected:
    void setOutputPins(uint8_t mask) override;
};

#endif // CLOCK_ACCEL_STEPPER_H