#pragma once

#include <Servo.h>

class Mechanics
{
private:
    Servo power;
    Servo servo;
    int _correction = 0;

public:
    Mechanics()
    {
        init();
    }

    void run(int speed, int angle)
    {
        speed = constrain(speed, -500, 500);
        power.writeMicroseconds(1500 + speed);

        angle = 90 + constrain(angle, -30, 30) + _correction;
        servo.write(angle);
    }

    void setServoCorrection(int correction)
    {
        this->_correction = correction;
    }

private:
    void init()
    {
        power.attach(9);
        servo.attach(10);
    }
};
