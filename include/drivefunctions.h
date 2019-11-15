#ifndef DRIVER_FUNCTIONS_H
#define DRIVER_FUNCTIONS_H

#include "vex.h"
using namespace vex;

//Makes the bot accelerate smoothly, leading to less jerk and more accurate movements.
//Possibly make the drive command use the gyro to make sure that the robot is not turning or not going in a straight line
void drive(double rev, int maxVel = 80, bool pidOn = true, bool correct = true, bool waitForCompletion = false)
{   
    if(waitForCompletion)
    {
      pidOn = false;
    }
    if(!pidOn)
    {
      d.spinFor(directionType::fwd, rev, rotationUnits::rev, maxVel, velocityUnits::pct, waitForCompletion);
      goto end;
    }
    if(rev > 0)
    {
      double vInitial = maxVel*.3;
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
      if(!correct)
      {
        goto end;
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
      double vInitial = maxVel*.3;
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
      if(!correct)
      {
        goto end;
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

void beginAccelerateDrive(double rev, int maxVel)
{   
    if(rev > 0)
    {
      double vInitial = maxVel*.2;
      maxVel -= vInitial;
      d.resetPosition();
      double error = rev - d.rotation(rotationUnits::rev);
      while(error > 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = (sin((M_PI/2)*x)*maxVel)+vInitial;
        dt.drive(directionType::fwd, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      dt.stop();
    }
    else if(rev < 0)
    {
      double vInitial = maxVel*.2;
      maxVel -= vInitial;
      d.resetPosition();
      double error = rev - d.rotation(rotationUnits::rev);
      while(error < 0)
      {
        error = rev - d.rotation(rotationUnits::rev);
        double x = (error)/rev;
        double vel = (sin((M_PI/2)*x)*maxVel)+vInitial;
        dt.drive(directionType::rev, vel, velocityUnits::pct);
        vex::task::sleep(20);
      }
      dt.stop();
    }
    end:
    vex::task::sleep(10);
}

void flipOut()
{
    Lift.spinFor(.3, rev, 75, velocityUnits::pct);
    drive(-.1, 40, false, false, false);
    vex::task::sleep(200);
    drive(.5, 40);
    drive(-.5, 40);
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

void liftTiltCheck()
{
  // -----------------------------Avoids Lift-Tilter conflict
        if(Lift.position(rotationUnits::rev) > 0 && Tilt.position(rotationUnits::rev) < .7)
        {
            Tilt.spinFor(directionType::fwd, .7 - Tilt.position(rotationUnits::rev), rotationUnits::rev, 100, velocityUnits::pct);
        }
        else if(Lift.position(rotationUnits::rev) < 0)
        {
            Tilt.spinTo(0, rotationUnits::rev, 70, velocityUnits::pct);
        }
}

void stack(void)
{
  intake.spin(directionType::fwd, 10, velocityUnits::pct);
  Tilt.spinFor(1.5, rev, 60, velocityUnits::pct, true);
  Tilt.spinFor(-1.5, rev, 60, velocityUnits::pct, false); //Used to be after the drive -.5 command
  drive(-.5, 40);
}

void getAutonInfo()
{
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("red");
      Controller1.Screen.print(rojo);
      Controller1.Screen.print(" sk");
      Controller1.Screen.print(skills);
      Controller1.Screen.print(" sl");
      Controller1.Screen.print(slow);
      Controller1.Screen.print(" test");
      Controller1.Screen.print(test);
}

#endif