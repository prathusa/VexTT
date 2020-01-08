//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
void RM()
{
    Brain.Timer.reset();
    double driveFwdDistance = 3.3;
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    intake.stop();
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    turnTo(155, true, 100);
    d.rotateFor(directionType::fwd, (2.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    stack();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

//drivetrain/gyro test
void BM()
{
    Brain.Timer.reset();
    double driveFwdDistance = 3.3;
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    intake.stop();
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(driveFwdDistance);
    intake.stop();
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.spin(reverse);
    vex::task::sleep(250);
    d.stop();
    turnTo(-155, true, 70);
    drive((2.0/3)*driveFwdDistance);
    stack();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}
#endif /* AUTONBM_H */?