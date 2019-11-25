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
        d.spin(directionType::fwd, vel, percentUnits::pct);
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

void pid()
{

}

void drivePID(double target) 
{
target *= 360 / (3.25 * M_PI);
d.resetRotation();

double kp = 0.33;
double ki = 0.0005;
double kd = 0.2;

double proportion;
double integralRaw;
double integral;
double integralActiveZone = 360 / (3.25 * M_PI);
double integralPowerLimit = 50 / ki;
double derivative;
double finalPower;

double error = target;
double lastError = target;
vex::task::sleep(50);
while(std::abs(error) > 75){
    error = target - d.rotation(rotationUnits::deg);
    if(error == 0){
        break;
    }
    proportion = kp * error;
    
    if(std::abs(error) < integralActiveZone && error != 0){
    integralRaw += error;
    } 
    else integralRaw = 0.0;
    
    if(integralRaw > integralPowerLimit){
        integralRaw = integralPowerLimit;
    }
    if(integralRaw < -integralPowerLimit){
        integralRaw = integralPowerLimit;
    }
    
    integral = ki * integralRaw;
    
    derivative = kd * (error - lastError);
    lastError = error;
    
    if(error == 0){
        derivative = 0;
        
    }
    finalPower = 0.5 * (proportion + integral + derivative);
    d.spin(fwd, finalPower, voltageUnits::volt);
    vex::task::sleep(20);
}
d.stop();
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
    Lift.spinFor(-.5, rev, 75, velocityUnits::pct, false);
    //drive(-.1, 60, false, false, false);
    intake.spin(vex::forward, 100, pct);
    Tilt.spinFor(2, rev, 127, velocityUnits::pct);
    Tilt.spinFor(-2, rev, 127, velocityUnits::pct);
    Lift.spinFor(-.1, rev, 75, velocityUnits::pct, true);
    intake.stop();
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
            Tilt.spinTo( .7, rotationUnits::rev, 100, velocityUnits::pct);
        }
        else if(Lift.position(rotationUnits::rev) < 0)
        {
            Tilt.spinTo(0, rotationUnits::rev, 70, velocityUnits::pct);
        }
}

void stack(void)
{
  double target = 1.8; //In revolutions
  double error = target - Tilt.position(rev);
  while(error > 0)
  {
    error = target - Tilt.position(rev);
    double volts = 4*sqrt(error)+3;
    Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    error = target - Tilt.position(rev);
    vex::task::sleep(20);
  }
  Tilt.stop();
}

//Added Controller and Brain feedback when autonomous is selected.
void autonController()
{
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      if(rojo)
      {
        Controller1.Screen.print("red");
      }

      if(azul)
      {
        Controller1.Screen.print("blue");
      }

      if(skills)
      {
        Controller1.Screen.print(" sk");
      }

      if(slow)
      {
        Controller1.Screen.print(" slow");
      }

      if(test)
      {
        Controller1.Screen.print(" test");
      }
}

void autonBrain()
{
      int pixelRow = 0;
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(fontType::mono30);
      Brain.Screen.setCursor(1, pixelRow);
      Brain.Screen.print("Selected: ");

      if(rojo)
      {
        Brain.Screen.print("red \n");
        //pixelRow += 30;
        //Brain.Screen.setCursor(1, pixelRow);
      }

      if(azul)
      {
        Brain.Screen.print("blue  \n");
        //pixelRow += 30;
        //Brain.Screen.setCursor(1, pixelRow);
      }

      if(skills)
      {
        Brain.Screen.print("skills  \n");
        //pixelRow += 30;
        //Brain.Screen.setCursor(1, pixelRow);
      }

      if(slow)
      {
        Brain.Screen.print("slow mode \n");
        //pixelRow += 30;
        //Brain.Screen.setCursor(1, pixelRow);
      }

      if(test)
      {
        Brain.Screen.print("test mode  \n");
        //pixelRow += 30;
        //Brain.Screen.setCursor(1, pixelRow);
      }
}

#endif