#pragma once

#include <Servo.h>

class Mechanics
{
private:
    Servo power;
    Servo servo;
    int _correction = 0;
    int _maxTurn = 25;

public:
    Mechanics()
    {
        init();
    }

    void run(int speed, int angle)
    {
        speed = constrain(speed, -500, 500);
        power.writeMicroseconds(1500 + speed);

        angle = 90 + constrain(angle, -_maxTurn, _maxTurn) + _correction;
        servo.write(angle);
    }

    void setServoCorrection(int correction)
    {
        this->_correction = correction;
    }

    void setMaxTurn(int maxTurn)
    {
        this->_maxTurn = maxTurn;
    }

private:
    void init()
    {
        power.attach(9);
        servo.attach(10);
    }
};
