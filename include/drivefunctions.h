#ifndef DRIVERFUNCTIONS_H
#define DRIVERFUNCTIONS_H

#include "vex.h"
#ifndef CONTROLS1_H
#define CONTROLS1_H
#include "controls.h"
#endif
using namespace vex;
ROBOT_BASE ROBOT;
ACCESS_OS OS;

void turnTo(double raw, int intakeSpeed, int timeout = 14)
{
  if (Inertial.installed()) 
  {
    double kP = 0.55;    //.5
    double kI = 0.00006; //.0035
    double kD = 0.45;   // 0.3
    double target = raw;
    double error = target - Inertial.rotation(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    int motionless = 0;
    while (std::abs(error) > 0 && (motionless <= timeout))
    {
      intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      //controls();
      //intake.spin(directionType::rev, 100, velocityUnits::pct);
      error = target - Inertial.rotation(rotationUnits::deg);
      integral += error;
      if (error == 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      l.spin(fwd, volts, voltageUnits::volt);
      r.spin(reverse, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
    goto end; 
  }
end:
  vex::task::sleep(20);
}

void marginalTurnTo(double raw, int intakeSpeed, double marginOfError = 0.5)
{
  if (Inertial.installed()) 
  {
    double kP = 0.45;    //.5
    double kI = 0.00006; //.0035
    double kD = 0.5;   // 0.3
    double target = raw;
    double error = target - Inertial.rotation(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    while (std::abs(error) > marginOfError)
    {
      intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      //controls();
      //intake.spin(directionType::rev, 100, velocityUnits::pct);
      error = target - Inertial.rotation(rotationUnits::deg);
      integral += error;
      if (error == 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      l.spin(fwd, volts, voltageUnits::volt);
      r.spin(reverse, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
    goto end; 
  }
end:
  vex::task::sleep(20);
}

void turn(double raw, int intakeSpeed = 0, int timeout = 1, double marginOfError = 0.5)
{
	//ROBOT.timeOut(2.5);
	//ROBOT.reset();

	if (OS.getValues(COLOR) == BLUE) //If color is 0 (BLUE) flip the values 
		raw = -raw;

  if(timeout == 0)
    marginalTurnTo(raw, intakeSpeed, marginOfError);
  else
	  turnTo(raw, intakeSpeed, timeout);
}

void turnFor(double raw, bool timeout = false, int time = 250) 
{
  if (Inertial.installed()) 
  {
      double kP = 0.1;    //.5
      double kI = 0.00065; //.0035
      double kD = 0.022;   // 0.3
      double target = Inertial.rotation(rotationUnits::deg) + raw;
      double error = target - Inertial.rotation(rotationUnits::deg);
      double integral = error;
      double prevError = error;
      double derivative = error - prevError;
      int motionless = 0;
      while (std::abs(error) > 0 && (motionless < time || !timeout))
      {
        controls();
        error = target - Inertial.rotation(rotationUnits::deg);
        integral += error;
        if (error == 0) 
        {
          integral = 0;
        }
        derivative = error - prevError;
        prevError = error;
        double volts = error * kP + integral * kI + derivative * kD;
        l.spin(fwd, volts, voltageUnits::volt);
        r.spin(reverse, volts, voltageUnits::volt);
        if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
        vex::task::sleep(15);
      }
      goto end; 
  }
end:
  vex::task::sleep(20);
}

//Left turning is broken
void turnToHeading(double target, int timeout = 250) 
{
  double rotation = Inertial.rotation(rotationUnits::deg);
  while(rotation >= 360)
  {
    target += 360;
    rotation -= 360;
  }
  while(rotation <= 0)
  {
    target -= 360;
    rotation += 360;
  }
  turnTo(target, timeout);
}

void tiltTo(int potentiometerPCT, double volts, bool slowDown = false) 
{
  double target = potentiometerPCT; // In revolutions
  double error = target - tilt.value(percentUnits::pct);
  if (std::abs(error) == 0)
    goto end;
  while (std::abs(error) > 0 && !slowDown) 
  {
    controls();
    if (error > 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    } 
    else if (error < 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      Tilt.spin(directionType::rev, volts, voltageUnits::volt);
    } 
    else
      goto end;

    vex::task::sleep(20);
  }
  // Not completed yet don't use!
  while (std::abs(error) > 0 && slowDown) 
  {
    controls();
    if (tilt.value(percentUnits::pct) < tiltStack) 
    {
      error = target - tilt.value(percentUnits::pct);
      double volts = .1 * error + 3;
      Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
      vex::task::sleep(20);
    } 
    else 
    {
      error = 0;
      double volts = error + 3;
      Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    }
  }
end:
  Tilt.stop();
}

void tiltFor(int potentiometerPCT, double volts) 
{
  int start = tilt.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  tiltTo(target, volts);
}

void tiltTo(int potentiometerPCT) 
{
  double error = potentiometerPCT - tilt.value(pct);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = .55;    // 0.15
  double kI = 0.002;    // 0.03
  double kD = 0.04;    // 0.1
  if (error > 0) 
  {
    while (std::abs(error) > 0) 
    {
      controls();
      error = potentiometerPCT - tilt.value(pct);
      integral += error;
      if (error <= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      Tilt.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (std::abs(error) > 0) 
    {
      controls();
      error = potentiometerPCT - tilt.value(pct);
      integral += error;
      if (error >= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      Tilt.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
}

void tiltFor(int potentiometerPCT) 
{
  int start = tilt.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  tiltTo(target);
}

void liftTiltCheck() 
{
  // -----------------------------Avoids Lift-Tilter conflict
  Lift.setBrake(hold);
  Tilt.setBrake(hold);
  if (lift.value(pct) > 32 && tilt.value(percentUnits::pct) < 31) 
  {
    tiltTo(31, 12);
  } 
  else if (lift.value(pct) <= 32 && tilt.value(percentUnits::pct) >= 31) 
  {
    tiltTo(tiltMin, 12);
  }
}

void liftTo(int potentiometerPCT, double volts) 
{
  double target = potentiometerPCT; // In revolutions
  double error = target - lift.value(percentUnits::pct);
  if (std::abs(error) == 0)
    goto end;
  while (std::abs(error) > 0) 
  {
    controls();
    liftTiltCheck();
    if (error > 0) 
    {
      error = target - lift.value(percentUnits::pct);
      Lift.spin(directionType::fwd, volts, voltageUnits::volt);
    } 
    else if (error < 0) 
    {
      error = target - lift.value(percentUnits::pct);
      Lift.spin(directionType::rev, volts, voltageUnits::volt);
    } 
    else
      goto end;

    vex::task::sleep(20);
  }
end:
  Tilt.stop();
}

void liftFor(int potentiometerPCT, double volts) 
{
  int start = lift.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  liftTo(target, volts);
}

void liftTo(int potentiometerPCT) 
{
  bool timeout = true;
  int time = 14; //if no movement in 15ms after no movement then task breaks
  double error = potentiometerPCT - lift.value(pct);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = .55;    // 0.15
  double kI = 0.0066;    // 0.03
  double kD = 0.04;    // 0.1
  int motionless = 0;
  if (error > 0) 
  {
    while (std::abs(error) > 0 && (motionless < time || !timeout)) 
    {
      controls();
      liftTiltCheck();
      error = potentiometerPCT - lift.value(pct);
      integral += error;
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      Lift.spin(fwd, volts, voltageUnits::volt);
      if(Lift.velocity(percentUnits::pct) == 0)
      {
        motionless+=15;
      }
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (std::abs(error) > 0 && (motionless < time || !timeout)) 
    {
      controls();
      liftTiltCheck();
      error = potentiometerPCT - lift.value(pct);
      integral += error;
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      Lift.spin(fwd, volts, voltageUnits::volt);
      if(Lift.velocity(percentUnits::pct) == 0)
      {
        motionless+=15;
      }
      vex::task::sleep(15);
    }
  }
}

void liftFor(int potentiometerPCT) 
{
  int start = lift.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  liftTo(target);
}


void flipOut() 
{
  liftTo(liftMin+14, 12);
  vex::task::sleep(200);
  liftTo(liftMin, 12);
  vex::task::sleep(500);
}

void stack(void) 
{
  double target = tiltStack; // In revolutions
  double error = target - tilt.value(percentUnits::pct);
  while (error > 0) 
  {
    controls();
    error = target - tilt.value(percentUnits::pct);
    double volts = .2 * error + 2; //.15 * error + 2; //.2 * error + 2 (2.550s)
    Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    vex::task::sleep(20);
  }
  intake.stop();
  Tilt.stop();
}

void towerLow(void) 
{
  liftTo(liftTowerLow, 12);
}

void towerMid(void) 
{
  liftTo(liftTowerMid, 12);
}

void fadeAway()
{
  intake.spinFor(directionType::rev, -2, rotationUnits::rev, 35, velocityUnits::pct, false); //possible reduction needed
  d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);
}

void fadeAwayMid()
{
  intake.spinFor(directionType::rev, -2, rotationUnits::rev, 65, velocityUnits::pct, false); //possible reduction needed
  d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);
}

// Added Controller and Brain feedback when autonomous is selected.
void autonController() 
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  if (rojo) 
  {
    Controller1.Screen.print("RED");
  }

  if (azul) 
  {
    Controller1.Screen.print("BLUE");
  }

  if (skills) 
  {
    Controller1.Screen.print(" SK");
  }

  if (slow) 
  {
    Controller1.Screen.print(" SLOW");
  }

  if (test) 
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

  if (rojo) 
  {
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("RED");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (azul) 
  {
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("BLUE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (skills) 
  {
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.print("SKILLS");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (slow) 
  {
    Brain.Screen.setFillColor(orange);
    Brain.Screen.print("SLOW MODE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }

  if (test) 
  {
    Brain.Screen.setFillColor(purple);
    Brain.Screen.print("TEST MODE");
    row += 1;
    Brain.Screen.setCursor(row, 0);
  }
}

void resetEncoders(void) 
{
  Lift.resetPosition();
  Tilt.resetPosition();
  LeftIntake.resetPosition();
  RightIntake.resetPosition();
  LeftFrontMotor.resetPosition();
  LeftRearMotor.resetPosition();
  RightFrontMotor.resetPosition();
  RightRearMotor.resetPosition();
}

void driveTo(double positionRev, int intakeSpeed = 0, int timeout = 50, double kP = 2, double kI = 0.0075, double kD = 6) 
{
  double error = positionRev - d.position(rotationUnits::rev);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  int motionless = 0;
  if (error > 0) 
  {
    while (error > 0 && motionless <= timeout) 
    {
      if(tilt.value(percentUnits::pct) - tiltStack > -3 && dt.velocity(percentUnits::pct) < 0)
        intake.spin(directionType::rev, dt.velocity(percentUnits::pct), percentUnits::pct);
      else
        intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      error = positionRev - d.position(rotationUnits::rev);
      integral += error;
      if (error <= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless=0;
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (error < 0 && motionless <= timeout) 
    {
      if(tilt.value(percentUnits::pct) - tiltStack > -3 && dt.velocity(percentUnits::pct) < 0)
        intake.spin(directionType::rev, dt.velocity(percentUnits::pct), percentUnits::pct);
      else
        intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      error = positionRev - d.position(rotationUnits::rev);
      integral += error;
      if (error >= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error * kP + integral * kI + derivative * kD;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless=0;
      vex::task::sleep(15);
    }
  }
  intake.stop();
}

void driveFor(double positionRev, int driveSpeed = 50, int intakeSpeed = 0, int timeout = 50) 
{
  double error = positionRev - d.position(rotationUnits::rev);
  double kP = driveSpeed/28.57;
  int motionless = 0;
  if (error > 0) 
  {
    while (error > 0 && motionless <= timeout) 
    {
      if(tilt.value(percentUnits::pct) - tiltStack > -3 && dt.velocity(percentUnits::pct) < 0)
        intake.spin(directionType::rev, dt.velocity(percentUnits::pct), percentUnits::pct);
      else
        intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      error = positionRev - d.position(rotationUnits::rev);
      double volts = (error * kP) + 2;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (error < 0 && motionless <= timeout) 
    {
      if(tilt.value(percentUnits::pct) - tiltStack > -3 && dt.velocity(percentUnits::pct) < 0)
        intake.spin(directionType::rev, dt.velocity(percentUnits::pct), percentUnits::pct);
      else
        intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      error = positionRev - d.position(rotationUnits::rev);
      double volts = (error * kP) - 2;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
  }
  intake.stop();
}

void drive(double revolutions, int intakeSpeed = 0, int timeout = 50, double kP = 2, double kI = 0.0075, double kD = 6) 
{
  double target = revolutions + d.position(rotationUnits::rev);
  driveTo(target, intakeSpeed, timeout, kP, kI, kD);
}

/*
//-------------------------Method 1 (Guess and Check):

First of all, set all three constants (kP, kI, kD) to zero. This “disables
them”. Tune them one by one, rather than jumping straight in. Generally tune in
the order of Proportional, Derivative, Integral, that is, tune in the order of
kP, kD and finally kI. This entire process relies on making a prediction for the
constant (“trial”), and then adjusting it when it doesn’t go to plan (“error”).
//Scientific Method, isolate one independent variable and observe dependant
variables to It’s important to be prepared to stop your robot (both by disabling
it from your program or a switch, and by physically catching it if necessary),
as you’ll likely make a prediction that is far off an appropriate value. So long
as you’re ready, there typically isn’t too much harm in just experimenting.

1. Increase kP until the robot oscillates just slightly, once or twice.
  We’re interested in achieving a fast motion to the target here, but not too
violent – it needs to settle, and in a reasonable amount of time!
2.  Start adding kD until the steady-state error starts to decrease until
something suitable. This will allow us to maintain the fast motion from the
Proportional component, whilst minimising the overshoot. You may need to go back
to adjusting kP a little.
3. Start adding kI until any minor steady-state error and disturbances are
accounted for. You may need to adjust kD when doing this.
4. Using the knowledge from the table on the previous page, keep adjusting the
constants until you end up with a nice, quick but smooth motion that you’re
happy with.

//-------------------------Method 2 (Ziegler-Nichols Mathematical Model):

Begin by disabling all three constants (set them to zero).
1. Increase kP until you get steady continuous oscillations.
  These need to be stable and consistent. Record this value as “kU” (ultimate or
critical gain).
2. Measure the period of the oscillations caused by step 1.
  That is, the time it takes to do a full cycle from a point back to itself. You
can measure this with a bit of programming, or with a stopwatch. It’s a good
idea to measure many oscillations and then divide the time by the number of
oscillations to get a good average. Record this number as “pU” (period for
ultimate or critical gain).
3. Calculate the approximate constant values from the following table:

       kP        kI         kD
PID  0.6*kU  1.2*kU/pU  0.075*kU*pU

*/

// Makes the bot accelerate smoothly, leading to less jerk and more accurate
// movements. Possibly make the drive command use the gyro to make sure that the
// robot is not turning or not going in a straight line

#endif
