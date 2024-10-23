#define DEBUG true

#include <Arduino.h>
#include <PIDController.h>
#include <Robot.h>

Robot *robot;

PIDController *pid;

void setup()
{

#ifdef DEBUG
    Serial.begin(115200);
    Serial.println("start");
#endif

    robot = new Robot();
    robot->setServoCorrection(-4);
    robot->setMaxTurn(20);

    pid = new PIDController();

    pid->tune(0.1, 0.0, 0.2);
    pid->limit(-30, 30);
    pid->setpoint(0);

    delay(500);
}

void loop()
{
    robot->readData();

    int speed = 50;

    int error = robot->l45d - robot->r45d;
    int angle = pid->compute(error);

    robot->run(speed, angle);
}
