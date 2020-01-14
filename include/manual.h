//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
void autonFrontRow()
{
    Brain.Timer.reset();
    double driveFwdDistance = 2;
    resetEncoders();
    Inertial.resetRotation();
    //d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    flipOut();
    Lift.stop();
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    //turnTo(0, true, 50);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 75, velocityUnits::pct, true);
    //drive((-1.0/3)*driveFwdDistance);
    //d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    turn(-45, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.3, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-37.5, true, 10); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .7, rotationUnits::rev, 50, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -.7, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-195, true, 10);
    d.rotateFor(directionType::fwd, 1.8, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-90, true, 10);
    d.rotateFor(directionType::fwd, 1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-100, true, 10);
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
	/*
    turn(-120, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-135, true, 10); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .9, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .3, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    vex::task::sleep(250); //possibly can reduce this number or removeable
    */
    intake.spin(directionType::fwd, 10, velocityUnits::pct); //can run this to lower cubes
    intake.stop();
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true); //untested I believe may need to be removed
    vex::task::sleep(200); //untested I believe may need to be removed
    intake.stop();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void autonBackRow()
{
	  Brain.Timer.reset();
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 3.6, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(30, true, 10);
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    d.rotateFor(directionType::fwd, -2.4, rotationUnits::rev, 80, velocityUnits::pct, true);
    turn(0, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(130, true, 10);
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.8, rotationUnits::rev, 70, velocityUnits::pct, true);
    intake.spin(directionType::fwd, 10, velocityUnits::pct);
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(200); //might need to be increased
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void autonSkills()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 8.2;
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance+.2, rotationUnits::rev, 40, velocityUnits::pct, true);
    intake.stop();
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 60, velocityUnits::pct, true);
    turn(45, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 60, velocityUnits::pct, true);
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void autonAmbi()
{
	d.rotateFor(directionType::fwd, -2, rotationUnits::rev, 50, velocityUnits::pct, false);
  vex::task::sleep(3000);
  drive(2);
}
/*
void autonFrontRow()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 3.2;
    resetEncoders();
    Inertial.resetRotation();
    //d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    flipOut();
    Lift.stop();
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 75, velocityUnits::pct, true);
    //drive((-1.0/3)*driveFwdDistance);
    //d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-120, true, 100); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-135, true, 100); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .9, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .3, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    vex::task::sleep(400); //possibly can reduce this number or removeable
    //intake.spin(directionType::fwd, 10, velocityUnits::pct); //can run this to lower cubes
    //vex::task::sleep(200); //can run this to lower cubes
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true); //untested I believe may need to be removed
    vex::task::sleep(200); //untested I believe may need to be removed
    intake.stop();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void autonFrontRow()
{
    Brain.Timer.reset();
    double driveFwdDistance = 3.2;
    resetEncoders();
    Inertial.resetRotation();
    //d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    flipOut();
    Lift.stop();
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 75, velocityUnits::pct, true);
    //drive((-1.0/3)*driveFwdDistance);
    //d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    vex::task::sleep(400);
    d.rotateFor(directionType::fwd, .8, rotationUnits::rev, 50, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -.8, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-120, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-135, true, 10); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .9, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .3, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    vex::task::sleep(250); //possibly can reduce this number or removeable
    intake.spin(directionType::fwd, 10, velocityUnits::pct); //can run this to lower cubes
    vex::task::sleep(200); //can run this to lower cubes
    intake.spin(directionType::rev, 20, velocityUnits::pct); //can run this to lower cubes
    vex::task::sleep(200); //can run this to lower cubes
    intake.stop();
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true); //untested I believe may need to be removed
    vex::task::sleep(200); //untested I believe may need to be removed
    intake.stop();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void autonBackRow()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance+.2, rotationUnits::rev, 40, velocityUnits::pct, true);
    intake.stop();
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 60, velocityUnits::pct, true);
    turn(150, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.1, rotationUnits::rev, 60, velocityUnits::pct, true);
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(200); //might need to be increased
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}
*/



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
#endif
