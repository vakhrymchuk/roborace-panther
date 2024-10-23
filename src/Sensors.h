#pragma once

#include <Wire.h>
#include <MedianFilterWindow.h>
#include <Vl53l0xSensorPin.h>
#include <Vl53l1xSensorPin.h>
#include <i2cScanner.h>
#include "MPU.h"

class Sensors
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

    int absolutAngle = 0;

private:
    static const long FAST_CLOCK = 400000;


    DistanceSensor *l90 = createSensorVl0X(2);
    DistanceSensor *r90 = createSensorVl0X(A0);
    DistanceSensor *l0 = createSensorVl1X(3);
    DistanceSensor *r0 = createSensorVl1X(A1);
    DistanceSensor *l45 = createSensorVl1X(A2);
    DistanceSensor *r45 = createSensorVl1X(A3);

    MPU mpu;

    int rotates = 0;
    float prevYaw = 0;

public:
    Sensors()
    {
        init();
    }

    void readData()
    {
        l90d = l90->getDistance();
        r90d = r90->getDistance();
        l0d = l0->getDistance();
        r0d = r0->getDistance();
        l45d = l45->getDistance();
        r45d = r45->getDistance();

        mpu.readData(yaw, pitch, roll);

        if (yaw * prevYaw < 0 && abs(yaw) > 90)
        {
            rotates += (yaw < 0) ? 1 : -1;
        }
        prevYaw = yaw;
        absolutAngle = rotates * 360 + yaw;

#ifdef DEBUG_SENSORS
        Serial.print("\tl90 = ");
        Serial.print(l90d);
        Serial.print("\tl45 = ");
        Serial.print(l45d);
        Serial.print("\tl0 = ");
        Serial.print(l0d);

        Serial.print("\tr0 = ");
        Serial.print(r0d);
        Serial.print("\tr45 = ");
        Serial.print(r45d);
        Serial.print("\tr90 = ");
        Serial.print(r90d);

        Serial.print("\t\tyaw = ");
        Serial.print(yaw);
        Serial.print("\tpitch = ");
        Serial.print(pitch);
        Serial.print("\troll = ");
        Serial.print(roll);
        Serial.print("\tabsolutAngle = ");
        Serial.print(absolutAngle);
        Serial.println();
#endif
    }

private:
    void init()
    {
        Wire.begin();
        Wire.setClock(FAST_CLOCK);

        l0->initSensor();
        r0->initSensor();
        l45->initSensor();
        r45->initSensor();
        l90->initSensor();
        r90->initSensor();

        mpu.init();
    }

    static DistanceSensor *createSensorVl0X(const byte pin)
    {
        DistanceSensor *sensor = new Vl53l0xSensorPin(pin, NORMAL);
        return new MedianFilterWindow(sensor);
    }
    static DistanceSensor *createSensorVl1X(const byte pin)
    {
        DistanceSensor *sensor = new Vl53l1xSensorPin(pin);
        return new MedianFilterWindow(sensor);
    }
};
