//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
//drive command test
void RM()
{
    flipOut();
    correction();
    intake.spin(fwd, 127, velocityUnits::pct);
    drive(3.3, speed);
    intake.stop();
    intake.spin(fwd, 30, velocityUnits::pct);
    drive(-3.3, speed);
    drive(-.1, 50, false);
    vex::task::sleep(200);
    d.stop();
    drive(.7, speed);
    r.rotateFor(directionType::fwd, -1, rotationUnits::rev, 60, velocityUnits::pct, false);
    l.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 60, velocityUnits::pct);
    drive(.6, speed);
    intake.stop();
    intake.spin(directionType::rev, 15, velocityUnits::pct);
    Tilt.rotateFor(1.3, rev, 60, velocityUnits::pct, true);
    Tilt.rotateFor(.2, rev, 60, velocityUnits::pct, false);
    vex::task::sleep(300);
    drive(-.5, speed);
}

//drivetrain/gyro test
void BM()
{
    flipOut();
    intake.spin(vex::reverse, 127, velocityUnits::pct);
    drive(3.4, 80);
    intake.stop();
    intake.spin(vex::reverse, 20, velocityUnits::pct);
    //make sure that this uses gyro to calculate rotated degrees if not use turn while not command
    sdt.turnFor(-40, rotationUnits::deg, 40, velocityUnits::pct);
    //need to figure out a way to reduce/remove gyro drift
    drive(3.1, 80);
    intake.stop();
    intake.spin(directionType::fwd, 15, velocityUnits::pct);
    Tilt.rotateFor(1.5, rev, 40, velocityUnits::pct);
    vex::task::sleep(300);
    drive(-1, 40);
    /*
    flipOut();
    intake.spin(fwd, 127, velocityUnits::pct);
    d.spinFor(directionType::fwd, 3.5, rotationUnits::rev, 40, velocityUnits::pct);
    intake.stop();
    intake.spin(fwd, 30, velocityUnits::pct);
    d.spinFor(directionType::fwd, -3.5, rotationUnits::rev, 40, velocityUnits::pct);
    d.spinFor(directionType::fwd, .7, rotationUnits::rev, 40, velocityUnits::pct);
    LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    r.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 40, velocityUnits::pct);
    d.spinFor(directionType::fwd,.625, rotationUnits::rev, 35, velocityUnits::pct);
    intake.stop();
    intake.spin(directionType::rev, 15, velocityUnits::pct);
    Tilt.rotateFor(1.5, rev, 40, velocityUnits::pct);
    vex::task::sleep(300);
    d.spinFor(directionType::fwd, -.5, rotationUnits::rev, 40, velocityUnits::pct);
    */
}

#endif /* AUTONBM_H */