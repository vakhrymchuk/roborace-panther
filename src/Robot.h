#pragma once

#include "Sensors.h"
#include "Mechanics.h"

class Robot
{
public:
    int r90d = 0;
    int r0d = 0;
    int l45d = 0;
    int r45d = 0;
    int l0d = 0;
    int l90d = 0;

    int yaw = 0;
    int pitch = 0;
    int roll = 0;
    
    int absoluteAngle = 0;

private:
    Sensors *sensors = new Sensors();
    Mechanics *mechanics = new Mechanics();

public:
    void readData()
    {
        sensors->readData();
        r90d = sensors->r90d;
        r0d = sensors->r0d;
        l45d = sensors->l45d;
        r45d = sensors->r45d;
        l0d = sensors->l0d;
        l90d = sensors->l90d;

        yaw = sensors->yaw;
        pitch = sensors->pitch;
        roll = sensors->roll;

        absoluteAngle = sensors->absolutAngle;
    }

    void run(int speed, int angle)
    {
        mechanics->run(speed, angle);
    }
};
