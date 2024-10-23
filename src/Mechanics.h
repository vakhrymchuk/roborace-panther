#pragma once

#include <Servo.h>

class Mechanics
{
private:
    Servo power;
    Servo servo;

public:
    Mechanics()
    {
        init();
    }

    void run(int speed, int angle)
    {
        speed = constrain(speed, -500, 500);
        power.writeMicroseconds(1500 + speed);
        
        angle = 90 + constrain(angle, -30, 30);
        servo.write(angle);
    }

private:
    void init()
    {
        power.attach(9);
        servo.attach(10);
    }
};
