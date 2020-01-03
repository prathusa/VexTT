//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
void RM()
{
    double driveFwdDistance = 3.3;
    resetEncoders();
    Inertial.resetRotation();
    drive(.75);
    drive(-.75);
    flipOut();
    turnTo(0);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(driveFwdDistance);
    intake.stop();
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    drive((-1/3)*driveFwdDistance);
    //drive(-.1, 50, false);
    //vex::task::sleep(200);
    turnTo(155);
    drive((2/3)*driveFwdDistance);
    stack();
    vex::task::sleep(200);
    fadeAway();
    /*
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 40, velocityUnits::pct, true);
    //vex::task::sleep(200);
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 40, velocityUnits::pct, true);
    //drive(.5, 40);
    //drive(-.5, 40);
    flipOut();
    d.rotateFor(-.2, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.3, 60, true, true, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.3, 100, true, true, false);
    //drive(-.1, 40, false, false, false);
    //d.rotateFor(-.1, rotationUnits::rev, 40, velocityUnits::pct, true);
    //vex::task::sleep(200);
    drive(.9, 60);
    //LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    //LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    r.rotateFor(directionType::fwd, -1.1, rotationUnits::rev, 40, velocityUnits::pct, false);
    l.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 45, velocityUnits::pct);
    //drive(1.15, 40);
    d.rotateFor(.55, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(.3, rotationUnits::rev, 60, velocityUnits::pct, false);
    //vex::task::sleep(300);
    //d.rotateFor(-.1, rotationUnits::rev, 40, velocityUnits::pct, true);
    intake.stop();
    //intake.spin(directionType::fwd, 10, velocityUnits::pct);
    //drive(-.15,40);
    Tilt.spinFor(1.8, rev, 40, velocityUnits::pct, true);
    drive(-.7, 60);
    /*
    flipOut();
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.5, 40, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.5, 40, false);
    drive(.7, 40);
    //LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    //LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    l.rotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    r.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 40, velocityUnits::pct);
    drive(.65, 40);
    intake.stop();
    stack();



    /*
    //flipOut();
    //correction();
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.3, speed);
    intake.stop();
    intake.spin(directionType::rev, 10, velocityUnits::pct);
    drive(-3.3, speed);
    //drive(-.1, 50, false);
    //vex::task::sleep(200);
    d.stop();
    drive(.7, speed);
    r.rotateFor(directionType::fwd, -1, rotationUnits::rev, 60, velocityUnits::pct, false);
    l.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 60, velocityUnits::pct);
    drive(.65, speed);
    intake.stop();\
    //Stack:
    intake.spin(directionType::fwd, 10, velocityUnits::pct);
    Tilt.rotateFor(1.4, rev, 60, velocityUnits::pct, true);
    Tilt.rotateFor(.2, rev, 60, velocityUnits::pct, false);
    vex::task::sleep(200);
    //Alternatively, to stack you can use stack();
    drive(-.5, speed);
    */
}

//drivetrain/gyro test
void BM()
{
    double driveFwdDistance = 3.3;
    resetEncoders();
    Inertial.resetRotation();
    drive(.75);
    drive(-.75);
    flipOut();
    turnTo(0);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(driveFwdDistance);
    intake.stop();
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    drive((-1/3)*driveFwdDistance);
    //drive(-.1, 50, false);
    //vex::task::sleep(200);
    turnTo(-155);
    drive((2/3)*driveFwdDistance);
    stack();
    vex::task::sleep(200);
    fadeAway();
    
    /*
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 40, velocityUnits::pct, true);
    //vex::task::sleep(200);
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 40, velocityUnits::pct, true);
    //drive(.5, 40);
    //drive(-.5, 40);
    flipOut();
    d.rotateFor(-.2, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(300);
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.5, 60, true, true, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.5, 100, true, true, false);
    //drive(-.1, 40, false, false, false);
    //d.rotateFor(-.1, rotationUnits::rev, 40, velocityUnits::pct, true);
    //vex::task::sleep(200);
    drive(.9, 40);
    //LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    //LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    l.rotateFor(directionType::fwd, -1.1, rotationUnits::rev, 40, velocityUnits::pct, false);
    r.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 45, velocityUnits::pct);
    //drive(1.15, 40);
    d.rotateFor(.55, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(.3, rotationUnits::rev, 60, velocityUnits::pct, false);
    //vex::task::sleep(300);
    //d.rotateFor(-.1, rotationUnits::rev, 40, velocityUnits::pct, true);
    intake.stop();
    //intake.spin(directionType::fwd, 10, velocityUnits::pct);
    //drive(-.15,40);
    Tilt.spinFor(1.8, rev, 40, velocityUnits::pct, true);
    drive(-.7, 60);
    */
}

/*
    flipOut();
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.5, 40, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.5, 40, false);
    drive(.7, 40);
    LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    r.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 40, velocityUnits::pct);
    drive(.65, 40);
    intake.stop();
    stack();
*/
#endif /* AUTONBM_H */