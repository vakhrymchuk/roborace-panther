#pragma once

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Interval.h"

/**
 * Calculate yaw, pitch and roll
 */
class MPU
{
public:
private:
    MPU6050 mpu;
    uint8_t fifoBuffer[45]{};
    Interval interval = Interval(11);
    Quaternion q;
    VectorFloat gravity;
    float ypr[3]{};
    float _yaw = 0;
    float _pitch = 0;
    float _roll = 0;

public:
    void init()
    {
        mpu.initialize();
        mpu.dmpInitialize();
        mpu.setDMPEnabled(true);
    }

    void readData(int &yaw, int &pitch, int &roll)
    {
        if (interval.isReady() && mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
        {
            // расчёты
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

            // результат в радианах (-3.14, 3.14)
            // Serial.print(ypr[0]); // вокруг оси Z yaw 
            // Serial.print(ypr[1]); // вокруг оси Y pitch
            // Serial.print(ypr[2]); // вокруг оси X roll
            // для градусов можно использовать degrees()

            this->_yaw = degrees(ypr[0]);
            this->_pitch = degrees(ypr[1]);
            this->_roll = degrees(ypr[2]);
        }
        yaw = this->_yaw;
        pitch = this->_pitch;
        roll = this->_roll;
    }
};