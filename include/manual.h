//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;

//start lined up with 2 cubes in front 
void p3()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    //drive(1.65, 100, 30, 3, 0.015, 4);
    d.rotateFor(directionType::fwd, 1.35, rotationUnits::rev, 40, velocityUnits::pct, true);
    turn(-90, 100, 1); //100 (timeout) can be reduced
    //drive(1.65, 100, 30, 3, 0.015, 4);
    intake.stop();
    d.rotateFor(directionType::fwd, .6, rotationUnits::rev, 30, velocityUnits::pct, true);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 30, velocityUnits::pct, true);
    turn(-127, 100, 10); //100 (timeout) can be reduced
    //drive(.8, 100, 30, 3, 0.015, 4);
    drive(1, 100, 10, 4, 0.03, 2);
    intake.spinFor(fwd, 1, rotationUnits::rev);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    fadeAway();
     //untested I believe may need to be removed
    //vex::task::sleep(270); //untested I believe may need to be removed
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    //fadeAway();
    //drive(-.1, 0, 10, 4, 0.015, 3);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

//start lined up with 2 cubes in front 
void p4()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(3.3, 100);
    turn(-130, 100, 0); //100 (timeout) can be reduced
    drive(3.5, 100, 10, 3, 0.015, 4);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    //fadeAway();
    drive(-.75, 0, 10, 3, 0.015, 4);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

//start lined up with 2 cubes in front 
void p5()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    drive(1, 100);
    turn(45);
    intake.spinFor(1, rotationUnits::rev, 100, velocityUnits::pct);
    turn(0);
    drive(2.3, 100);
    turn(-130, 50, 0); //100 (timeout) can be reduced
    drive(3.5, 100, 10, 3, 0.015, 4);
    intake.spinFor(fwd, 1, rotationUnits::rev);
    stack();
    intake.spinFor(fwd, .65, rotationUnits::rev, 50, velocityUnits::pct);
    fadeAway();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

//start lined up to the right of red / left of blue, pre load off to the side (not being used)
void tp5()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(3.3, 100, 30, 3, 0.015, 4);
    turn(-90, 100, 0);
    drive(.5, 100, 30, 3, 0.015, 4);
    turn(-130, 100, 0); //100 (timeout) can be reduced
    drive(3.5, 100, 10, 3, 0.015, 4);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    //fadeAway();
    drive(-.75, 0, 10, 3, 0.015, 4);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

//start lined up to the right of red / left of blue, pre load off to the side (not being used)
void p6()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(3.3, 100, 10, 3, 0.015, 4);
    turn(-90, 100, 0);
    drive(.5, 100, 10);
    turn(-180, 100, 0);
    drive(3, 100, 10, 3, 0.015, 4);
    turn(-90, 100, 0);
    drive(3, 100, 10, 3, 0.015, 4);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    //fadeAway();
    drive(-.75, 0, 10, 3, 0.015, 4);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void u4()
{
	  Brain.Timer.reset();
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    // --> drive command stuffs here <--
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    //fadeAway();
    drive(-.75, 0, 10, 3, 0.015, 4);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void u5()
{
	  Brain.Timer.reset();
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100);//39);
    intake.spinFor(directionType::rev, 1, rotationUnits::rev, 50, velocityUnits::pct, false);
    intake.spinFor(fwd, .5, rotationUnits::rev, 30, velocityUnits::pct, false);
    d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(135, 50, 10);
    //intake.spinFor(fwd, .5, rotationUnits::rev, 70, velocityUnits::pct, true);
    drive(1.9, 100, 30, 3, 0.015, 4);//27);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, 1, rotationUnits::rev, 70, velocityUnits::pct);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    fadeAway();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void u6()
{
	  Brain.Timer.reset();
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.8, 100);//39);
    d.rotateFor(directionType::fwd, -1.9, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(140, 100, 0);
    drive(2.1, 100, 30, 3, 0.015, 4);//27);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .4, rotationUnits::rev, 30, velocityUnits::pct);
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void tu7()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100, 10);
    turn(30, 100, 10);
    drive(-3.5, 40, 30, 3, 0.015, 4);
    turn(0, 100, 10);
    drive(2.8, 100, 10);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    turn(130, 0, 0);
    drive(3, 0, 30, 3, 0.015, 4);//27);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, .5, rotationUnits::rev, 70, velocityUnits::pct);
    stack();
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void ttu7()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100);//39);
    turn(-90, 50, 10);
    d.rotateFor(directionType::fwd, 1.4, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-180, 100, 10);
    drive(1.4, 100, 10);
    turn(135, 100, 10);
    intake.spinFor(fwd, .5, rotationUnits::rev, 70, velocityUnits::pct, false);
    drive(2.4, 0, 30, 3, 0.015, 4);//27);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, .5, rotationUnits::rev, 70, velocityUnits::pct);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    //d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void u7()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100, 10);
    turn(-30, 100, 10);
    drive(-3.5, 40, 30, 3, 0.015, 4);
    turn(0, 100, 10);
    drive(2.9, 100, 10);
    intake.spinFor(fwd, .5, rotationUnits::rev, false);
    turn(134, 0, 0);
    drive(1.9, 100, 30, 3, 0.015, 4);//27);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, .5, rotationUnits::rev, 70, velocityUnits::pct);
    stack();
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void p8()
{
    Brain.Timer.reset();
    double t1;
    double t2;
    resetEncoders();
    Inertial.resetRotation();
    //vex::task::sleep(50);
    flipOut();
    Lift.stop();
    drive(2.1, 100, 30);
    turn(-30, 100, 10);
    drive(-1.8, 100, 30, 3, 0.015, 4);
    drive(2.6, 100, 30);
    //drive(-.9, 100, 30, 3, 0.015, 4);
    turn(-130, true, 100); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 40, velocityUnits::pct, true);
    turn(-135, true, 100); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 40, velocityUnits::pct, true);
    vex::task::sleep(400);
    intake.spin(directionType::fwd, 25, velocityUnits::pct);
    d.rotateFor(directionType::fwd, .25, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    vex::task::sleep(400); //possibly can reduce this number or removeable
    //intake.spin(directionType::fwd, 10, velocityUnits::pct); //can run this to lower cubes
    //vex::task::sleep(200); //can run this to lower cubes
    stack();
    d.rotateFor(directionType::fwd, .08, rotationUnits::rev, 25, velocityUnits::pct, true); //untested I believe may need to be removed
    vex::task::sleep(275); //untested I believe may need to be removed
    intake.stop();
    //vex::task::sleep(200);
    d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void s18()
{
	  Brain.Timer.reset();
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(1, 100, 30, 3, 0.015, 4);
    towerMid();
    intake.spinFor(fwd, .5, rotationUnits::rev);
    drive(.75, 100, 30, 3, 0.015, 4);
    fadeAway();
    liftTo(liftMin, 12);
    drive(-2, 0, 100);
    turn(0);
    drive(9.5, 100, 10, 1.5, 0.0015, 4.5);//39);
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(45, 100, 40);
    drive(1.9, 100, 10, 3, 0.015, 4);//27);
    intake.spinFor(fwd, 1, rotationUnits::rev);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .35, rotationUnits::rev, 30, velocityUnits::pct);
    fadeAway();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void s40()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100, 10, 7, 0.0075, 6);//39);
    turn(-30, 100, 40);
    intake.spin(directionType::rev, 100, percentUnits::pct);
    drive(1, 100);
    drive(-1, 100);
    turn(0, 50);
    d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(140, 100, 40);
    drive(1.9, 100, 30, 3, 0.015, 4);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, 1, rotationUnits::rev);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    intake.stop();
    turn(-90);
    drive(3, 100);
    drive(-.5, -10);
    towerMid();
    drive(.55, 0, 30);
    fadeAway();
    d.rotateFor(directionType::rev, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    liftTo(liftMin, 12);
    turn(0, 100);
    drive(0.5, 100, 10, 2, .5, 4);
    turn(90, 100);
    drive(3, -10);
    drive(-.5, -10);
    towerLow();
    drive(.55, 0, 30);
    fadeAway();
    turn(-15);
    drive(2.1, 100, 10);
    drive(-.5, -10);
    towerLow();
    drive(.55, 0, 30);
    fadeAway();
    turn(0);
    drive(4, 100);
    d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(45, 100, 40);
    drive(1.9, 100, 30, 3, 0.015, 4);
    d.rotateFor(directionType::fwd, -.085, rotationUnits::rev, 25, velocityUnits::pct, true);
    intake.spinFor(fwd, 1, rotationUnits::rev);
    stack();
    //d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(270); //might need to be increased
    intake.spinFor(fwd, .65, rotationUnits::rev, 30, velocityUnits::pct);
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void autonAmbi()
{
	drive(-2);
  drive(2);
  flipOut();
}
#endif
