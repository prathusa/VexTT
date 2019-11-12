#ifndef DRIVER_FUNCTIONS_H
#define DRIVER_FUNCTIONS_H

#include "vex.h"
using namespace vex;

void drive(double rotations, double speed, bool waitForCompletion)
{
    d.spinFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct, waitForCompletion);
}

//Makes the bot accelerate smoothly, leading to less jerk and more accurate movements.
//Possibly make the drive command use the gyro to make sure that the robot is not turning or not going in a straight line
void drive(double rev, int maxVel)
{   
    if(rev > 0)
    {
      double vInitial = maxVel*.1;
      maxVel -= vInitial;
      d.resetPosition();
      double error = rev - d.rotation(rotationUnits::rev);
      while(error > 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = (sin(M_PI*x)*maxVel)+vInitial;
        dt.drive(directionType::fwd, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      if(error == 0)
      {
        goto end;
      }
      //Corrects overshoot
      while(error < 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = vInitial;
        dt.drive(directionType::rev, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      dt.stop();
    }
    else if(rev < 0)
    {
      double vInitial = maxVel*.1;
      maxVel -= vInitial;
      d.resetPosition();
      double error = rev - d.rotation(rotationUnits::rev);
      while(error < 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = (sin(M_PI*x)*maxVel)+vInitial;
        dt.drive(directionType::rev, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      if(error == 0)
      {
        goto end;
      }
      //Corrects overshoot
      while(error > 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = vInitial;
        dt.drive(directionType::fwd, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      dt.stop();
    }
    end:
    vex::task::sleep(10);
}

void flipOut()
{
    Lift.spinFor(.3, rev, 75, velocityUnits::pct, false);
    d.rotateFor(directionType::fwd, .5, rotationUnits::rev, 80, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 80, velocityUnits::pct, true);
    Lift.spinFor(-.5, rev, 75, velocityUnits::pct, false);
    intake.spin(vex::forward);
    Tilt.spinFor(2, rev, 127, velocityUnits::pct);
    Tilt.spinFor(-2, rev, 127, velocityUnits::pct);
    Lift.spinFor(-.1, rev, 75, velocityUnits::pct, true);
    Lift.setBrake(brakeType::hold);
}

//Resets the robot's facing position to the Gyro's 0 degrees angle
//Needs to be tested
void correction()
{
    check:
    if(Gyro.angle() == 0)
    {
        goto end;
    }
    while(Gyro.angle() < 180)
    {
	      dt.turn(turnType::left, 20, velocityUnits::pct);
    }
	  if(Gyro.angle() == 0)
    {
        goto end;
    }
    while(Gyro.angle() > 180)
    {
        dt.turn(turnType::right, 20, velocityUnits::pct);
    }
	  if(Gyro.angle() == 0)
    {
        goto end;
    }
	  while(Gyro.angle() < 180)
    {
	      dt.turn(turnType::left, 20, velocityUnits::pct);
    }
    if(Gyro.angle() == 0)
    {
        goto end;
    }
    end:
    vex::task::sleep(20);
}

#endif