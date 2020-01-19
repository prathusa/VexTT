//Autonomus Manual Code
#ifndef MANUAL_H
#define MANUAL_H

#include "drivefunctions.h"

int speed = 80;
void motorAFR()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 3.2;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 75, velocityUnits::pct, true);
    turn(-120, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    vex::task::sleep(400);
    turn(-135, 10); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .8, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .3, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    intake.spin(directionType::rev, 25, velocityUnits::pct);
    vex::task::sleep(400); //possibly can reduce this number or removeable
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void AFR()
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
    turn(-130, 100, 10); //100 (timeout) can be reduced
    drive(3.5, 100, 10, 3, 0.015, 4);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void AFR1()
{
	  Brain.Timer.reset();
    double fwd1 = 37.5;
    double fwd2 = 36;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    Lift.stop();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    drive(3.2, 100);
    turn(-130); //100 (timeout) can be reduced
    drive(2, 100);
    turn(-135);
    drive(1.1);
    intake.spinFor(fwd, .5, rotationUnits::rev);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, false); //untested I believe may need to be removed
    vex::task::sleep(270); //untested I believe may need to be removed
    d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());
}

void motorABR()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance-.3, rotationUnits::rev, 45, velocityUnits::pct, true); //3.2
    intake.spin(directionType::rev, 12, voltageUnits::volt);
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 20, velocityUnits::pct, true);
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 45, velocityUnits::pct, true); //
    turn(150, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.1, rotationUnits::rev, 60, velocityUnits::pct, true);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 25, velocityUnits::pct);
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void ABR()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.3, 100);//39);
    d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(140, 100, 10);
    drive(2.1, 100, 30, 3, 0.015, 4);//27);
    intake.spin(directionType::fwd, 15, percentUnits::pct);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void encoderABR()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    trackFor(39);
    intake.spin(directionType::rev, 12, voltageUnits::volt);
    trackFor(-5);
    turn(150);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    trackFor(27);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 25, velocityUnits::pct);
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

void autonFrontRow()
{
	  AFR();
}
void autonBackRow()
{
	  ABR();
}

//8pnt
/*
void autonFrontRow()
{
    Brain.Timer.reset();
    double t1;
    double t2;
    resetEncoders();
    Inertial.resetRotation();
    //vex::task::sleep(50);
    flipOut();
    t1 = Brain.Timer.time();
    Lift.stop();
    d.rotateFor(directionType::fwd, 2, rotationUnits::rev, 65, velocityUnits::pct, true);
    t2 = Brain.Timer.time();
    turn(-30, true, 10);
    intake.spin(directionType::rev, 65, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.8, rotationUnits::rev, 55, velocityUnits::pct, true);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, ., rotationUnits::rev, 35, velocityUnits::pct, true);
    vex::task::sleep(500);
    d.rotateFor(directionType::fwd, -.9, rotationUnits::rev, 35, velocityUnits::pct, true);
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
*/
/*
void autonFrontRow()
{
    Brain.Timer.reset();
    double driveFwdDistance = 3;
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
    //vex::task::sleep(400);
    //turn(-25, true, 10);
    //d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-120, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-135, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, .9, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .2, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
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

/*
void autonBackRow()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    //vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 12, voltageUnits::volt);
    d.rotateFor(directionType::fwd, 3.2, rotationUnits::rev, 40, velocityUnits::pct, true);
    turn(10);
    d.rotateFor(directionType::fwd, .8, rotationUnits::rev, 40, velocityUnits::pct, true);
    vex::task::sleep(500);
    intake.stop();
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 60, velocityUnits::pct, true);
    turn(140, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2, rotationUnits::rev, 60, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .2, rotationUnits::rev, 40, velocityUnits::pct, false);
    vex::task::sleep(300);
    stack();
    tiltTo(tiltMin, 12);
    intake.spin(directionType::fwd, 40, velocityUnits::pct);
    vex::task::sleep(200);
    //d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    //vex::task::sleep(275); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);    
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}

/*
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
    //turnTo(0, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 3.3, rotationUnits::rev, 37, velocityUnits::pct, true);
    intake.stop();
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    //drive((-1.0/3)*driveFwdDistance);
    d.rotateFor(directionType::fwd, -2.5/3, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(140, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.5, rotationUnits::rev, 60, velocityUnits::pct, true);
    //intake.spin(directionType::fwd, 35, velocityUnits::pct);
    d.rotateFor(directionType::fwd, .6, rotationUnits::rev, 60, velocityUnits::pct, false);
    vex::task::sleep(450);
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(275); //might need to be increased
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time());  
}
*/

void autonSkills()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(8, 100, 10, 7, 0.0075, 6);//39);
    d.rotateFor(directionType::fwd, -1.2, rotationUnits::rev, 50, velocityUnits::pct, true);
   // drive(-.4, 100. 10);//5);
    turn(45, 100, 40);
    drive(2.1, 100, 10, 3, 0.015, 4);//27);
    intake.spin(directionType::fwd, 15, percentUnits::pct);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
}

void experimentalSkills()
{
	  Brain.Timer.reset();
    double driveFwdDistance = 4;
    resetEncoders();
    Inertial.resetRotation();
    flipOut();
    drive(3.2, 100, 10, 7, 0.0075, 6);//39);
    turn(-30, 100, 40);
    intake.spin(directionType::rev, 100, percentUnits::pct);
    drive(1, 100);
    drive(-1, 100);
   // drive(-.4, 100. 10);//5);
    turn(140, 100, 40);
    drive(2.1, 100, 10, 3, 0.015, 4);//27);
    stack();
    d.rotateFor(directionType::fwd, .085, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(270); //might need to be increased
    d.spinFor(-.75, rotationUnits::rev, 50, velocityUnits::pct);
    intake.stop();
    
    turn(90);
    drive(3, 100);
    drive(-.5, -10);
    tower();
    fadeAway();
    d.rotateFor(directionType::rev, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    liftTo(liftMin, 12);
    turn(0, 100);
    drive(0.5, 100, 10, 2, .5, 4);
    turn(90, 100);
    drive(3, -10);
    tower();
    fadeAway();
    turn(-25);
    drive(2.1, 100);

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
    //Controller1.Screen.clearScreen();
    double driveFwdDistance = 2;
    resetEncoders();
    Inertial.resetRotation();
    //d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    flipOut();
    liftTo(liftMin);
    Lift.stop();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    d.rotateFor(directionType::fwd, 3.2, rotationUnits::rev, 75, velocityUnits::pct, true);
    //drive((-1.0/3)*driveFwdDistance);
    //d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-90, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, .7, rotationUnits::rev, 45, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -.6, rotationUnits::rev, 55, velocityUnits::pct, true);
    turn(0, true, 10);
    d.rotateFor(directionType::fwd, 1.3, rotationUnits::rev, 55, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -1.3, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-180, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 3, rotationUnits::rev, 45, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -.65, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-90, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 1.4, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(-135, true, 10);
    intake.spin(directionType::rev, 50, velocityUnits::pct);
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
	/*
    turn(-120, true, 10); //100 (timeout) can be reduced
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.0, rotationUnits::rev, 65, velocityUnits::pct, true);
    turn(-135, true, 10); //100 (timeout) can be reduced
    d.rotateFor(directionType::fwd, .9, rotationUnits::rev, 65, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, .3, rotationUnits::rev, 65, velocityUnits::pct, false); //possibly can reduce this number or removeable
    vex::task::sleep(250); //possibly can reduce this number or removeable
    *//*
     //can run this to lower cubes
    intake.stop();
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true); //untested I believe may need to be removed
    vex::task::sleep(200); //untested I believe may need to be removed
    intake.stop();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Total Time: %d ", Brain.Timer.time());  
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

//8pnt
void autonBackRow()
{
    Brain.Timer.reset();
    double t1;
    double t2;
    resetEncoders();
    Inertial.resetRotation();
    vex::task::sleep(50);
    //d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 50, velocityUnits::pct, true);
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    flipOut();
    t1 = Brain.Timer.time();
    liftTo(liftMin);
    Lift.stop();
    //d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    //vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 3.6, rotationUnits::rev, 50, velocityUnits::pct, true);
    t2 = Brain.Timer.time();
    turn(32, true, 10);
    intake.spin(directionType::rev, 40, velocityUnits::pct);
    d.rotateFor(directionType::fwd, -2.9, rotationUnits::rev, 80, velocityUnits::pct, true);
    turn(0, true, 10);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 2.1, rotationUnits::rev, 50, velocityUnits::pct, true);
    turn(125, true, 10);
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    d.rotateFor(directionType::fwd, 3.4, rotationUnits::rev, 70, velocityUnits::pct, true);
    intake.spin(directionType::rev, 50, velocityUnits::pct);
    stack();
    d.rotateFor(directionType::fwd, .075, rotationUnits::rev, 25, velocityUnits::pct, true);
    vex::task::sleep(200); //might need to be increased
    fadeAway();
    intake.stop();
    //Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Flipout: %d ", t1);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Line 1: %d ", t2);    
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Run Time: %d ", Brain.Timer.time());  
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
    turnTo(155, 100);
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
    turnTo(-155, 70);
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
