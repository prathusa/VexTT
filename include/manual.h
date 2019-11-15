//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
//drive command test
void RM()
{
    flipOut();
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.5, 40, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.5, 40, false);
    drive(.65, 40);
    //LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    //LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    r.rotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct, false);
    l.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 40, velocityUnits::pct);
    drive(.65, 40);
    intake.stop();
    stack();
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
    /*
    flipOut();
    intake.spin(vex::reverse, 127, velocityUnits::pct);
    drive(3.4, 50);
    intake.stop();
    intake.spin(vex::reverse, 20, velocityUnits::pct);
    //make sure that this uses gyro to calculate rotated degrees if not use turn while not command
    ///////////dt.turnFor(-40, rotationUnits::deg, 40, velocityUnits::pct);
    //need to figure out a way to reduce/remove gyro drift
    r.rotateFor(directionType::fwd, 1.4, rotationUnits::rev, 50, velocityUnits::pct, false);
    l.rotateFor(directionType::fwd, -1.6, rotationUnits::rev, 50, velocityUnits::pct);
    drive(3, 80);
    intake.stop();
    stack();
    drive(-1, 40);
    */
    
    flipOut();
    intake.spin(directionType::rev, 127, velocityUnits::pct);
    drive(3.5, 40, false);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    drive(-3.5, 40, false);
    drive(.65, 40);
    //LeftFrontMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    //LeftRearMotor.startRotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
    l.rotateFor(directionType::fwd, -1, rotationUnits::rev, 40, velocityUnits::pct, false);
    r.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 40, velocityUnits::pct);
    drive(.65, 40);
    intake.stop();
    stack();
}

#endif /* AUTONBM_H */