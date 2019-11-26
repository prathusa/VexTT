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

void pid(double rev)
{
  double error = rev - d.position(rotationUnits::rev);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = 0; //Guess and check to find this
  double kI = 0; //Guess and check to find this
  double kD = 0; //Guess and check to find this
  if(error > 0)
  {
    while(error > 0)
    {
      error = rev - d.position(rotationUnits::rev);
      integral += error;
      if(error <= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      d.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
  else if (error < 0)
  {
    while(error < 0)
    {
      error = rev - d.position(rotationUnits::rev);
      integral += error;
      if(error >= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      d.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
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
while(std::abs(error) > 75)
{
    error = target - d.rotation(rotationUnits::deg);
    if(error == 0)
    {
        break;
    }
    proportion = kp * error;
    
    if(std::abs(error) < integralActiveZone && error != 0)
    {
    integralRaw += error;
    } 
    else integralRaw = 0.0;
    
    if(integralRaw > integralPowerLimit)
    {
        integralRaw = integralPowerLimit;
    }
    if(integralRaw < -integralPowerLimit)
    {
        integralRaw = integralPowerLimit;
    }
    
    integral = ki * integralRaw;
    
    derivative = kd * (error - lastError);
    lastError = error;
    
    if(error == 0)
    {
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
    //drive(-.1, 60, false, false, false);
    intake.spin(vex::forward, 100, pct);
    Tilt.spinFor(2, rev, 127, velocityUnits::pct);
    Tilt.spinFor(-2, rev, 127, velocityUnits::pct);
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

void tiltTo(double targetDegrees)
{
  double error = targetDegrees - Potentiometer.angle(rotationUnits::deg);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = 4 * (1/360);
  double kI = 1/360;
  double kD = 1/360;
  if(error > 0)
  {
    while(error > 0)
    {
      error = targetDegrees - Potentiometer.angle(rotationUnits::deg);
      integral += error;
      if(error <= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      Tilt.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
  else if (error < 0)
  {
    while(error < 0)
    {
      error = targetDegrees - Potentiometer.angle(rotationUnits::deg);
      integral += error;
      if(error >= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      Tilt.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
}

void tiltFor(double revolutions)
{

}

void liftTiltCheck()
{
  // -----------------------------Avoids Lift-Tilter conflict
        if(Lift.position(rotationUnits::rev) > .3 && Tilt.position(rotationUnits::rev) < .7)
        {
            Tilt.spinTo( .7, rotationUnits::rev, 100, velocityUnits::pct);
        }
        else if(Lift.position(rotationUnits::rev) < .3)
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
        Controller1.Screen.print("RED");
      }

      if(azul)
      {
        Controller1.Screen.print("BLUE");
      }

      if(skills)
      {
        Controller1.Screen.print(" SK");
      }

      if(slow)
      {
        Controller1.Screen.print(" SLOW");
      }

      if(test)
      {
        Controller1.Screen.print(" TEST");
      }
}

void autonBrain()
{
      int row = 1;
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(fontType::mono60);
      Brain.Screen.setCursor(1, row);

      if(rojo)
      {
        Brain.Screen.setFillColor(red);
        Brain.Screen.print("RED");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(azul)
      {
        Brain.Screen.setFillColor(blue);
        Brain.Screen.print("BLUE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(skills)
      {
        Brain.Screen.setFillColor(yellow);
        Brain.Screen.print("SKILLS");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(slow)
      {
        Brain.Screen.setFillColor(orange);
        Brain.Screen.print("SLOW MODE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(test)
      {
        Brain.Screen.setFillColor(purple);
        Brain.Screen.print("TEST MODE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }
}





// ----------------------Reference PID Loop
/*

void drivePID(double target) {
target *= 360 / (3.25 * M_PI);
DLB.resetRotation();

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
sleepMs(50);
while(abs(error) > 75){
    error = target - DLB.rotation(rotationUnits::deg);
    if(error == 0){
        break;
    }
    proportion = kp * error;
    
    if(abs(error) < integralActiveZone && error != 0){
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
    driveForward(finalPower);
    sleepMs(20);
}
DLF.stop(brakeType::coast);
DLB.stop(brakeType::coast);
DRF.stop(brakeType::coast);
DRB.stop(brakeType::coast);
}

*/




#endif