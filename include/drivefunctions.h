#ifndef DRIVER_FUNCTIONS_H
#define DRIVER_FUNCTIONS_H

#include "vex.h"
using namespace vex;

double getEncoderPosition()
{
  //return -(re.position(rev) + le.position(rotationUnits::rev))/2;
  return -(le.position(rotationUnits::rev));
}
/*
void driveTo(double positionRev) 
{
  int dT = 15/1000;
  double error = positionRev - d.position(rotationUnits::rev);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = 4;    // 0.15
  double kI = .04 / dT; // 0.03
  double kD = 1.1 * dT;    // 0.1
  while (std::abs(error) > 0) 
  {
    error = positionRev - d.position(rotationUnits::rev);
    integral += error;
    if (error == 0) 
    {
      integral = 0;
    }
    derivative = error - prevError;
    prevError = error;
    double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
    d.spin(fwd, volts, voltageUnits::volt);
    vex::task::sleep(15);
    }
}

void drive(double revolutions) 
{
  double target = revolutions + d.position(rotationUnits::rev);
  driveTo(target);
}
*/

void driveTo(double positionRev) 
{
  double error = positionRev - getEncoderPosition();
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = 4;    // 0.15
  double kI = .035; // 0.03
  double kD = 1;    // 0.1
  int dT = 15/1000;
  if (error > 0) 
  {
    while (error > 0) 
    {
      error = positionRev - getEncoderPosition();
      integral += error;
      if (error <= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
      d.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (error < 0) 
    {
      error = positionRev - getEncoderPosition();
      integral += error;
      if (error >= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
      d.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
}

void drive(double revolutions) {
  double target = revolutions + getEncoderPosition();
  driveTo(target);
}

// BROKEN
/*
void turnTo(double raw)
{
  double kP = 0.1; //.5
  double kI = 0.001; //.0035
  double kD = 0.1; //0.3
  if(raw > 0)
  {
    double target = raw;
    double error = target - Gyro.value(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    while(std::abs(error) > 0)
    {
      error = target - Gyro.value(rotationUnits::deg);
      integral += error;
      if(error <= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      l.spin(fwd, volts, voltageUnits::volt);
      r.spin(reverse, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
    goto end;
  }
  else if (raw < 0)
  {
    double target = raw;
    double error = target + Gyro.value(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    while(std::abs(error) > 0)
    {
      error = target + Gyro.value(rotationUnits::deg);
      integral += error;
      if(error <= 0)
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = error*kP + integral*kI + derivative*kD;
      l.spin(reverse, volts, voltageUnits::volt);
      r.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
    goto end;
  }
  end:
  vex::task::sleep(20);
}
*/

void turnTo(double raw, bool timeout = false, int time = 250) 
{
  if (Inertial.installed()) 
  {
    double kP = 0.1;    //.5
    double kI = 0.0006; //.0035
    double kD = 0.03;   // 0.3
    double target = raw;
    double error = target - Inertial.rotation(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    int dT = 15/1000;
    int motionless = 0;
    while (std::abs(error) > 0 && (motionless < time || !timeout))
    {
      error = target - Inertial.rotation(rotationUnits::deg);
      integral += error;
      if (error == 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
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

void turnFor(double raw, bool timeout = false, int time = 250) 
{
  if (Inertial.installed()) 
  {
    double kP = 0.1;    //.5
    double kI = 0.0006; //.0035
    double kD = 0.03;   // 0.3
    double target = Inertial.rotation(rotationUnits::deg) + raw;
    double error = target - Inertial.rotation(rotationUnits::deg);
    double integral = error;
    double prevError = error;
    double derivative = error - prevError;
    int dT = 15/1000;
    int motionless = 0;
    while (std::abs(error) > 0 && (motionless < time || !timeout))
    {
      error = target - Inertial.rotation(rotationUnits::deg);
      integral += error;
      if (error == 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
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
void turnToHeading(double target, bool timeout = false, int time = 250) 
{
  if (Inertial.installed()) 
  {
    double kP = 0.4;    //.5
    double kI = 0.001; //.0035
    double kD = 2.3;   // 0.3 
    
    if(target < 0)
    {
      target += 360;
    }
    
    double error = target - Inertial.heading();
    int dT = 15/1000;
    int motionless = 0;
    if (error  <= 180) 
    {
      double error = target - Inertial.heading();
      double integral = error;
      double prevError = error;
      double derivative = error - prevError;
      while (std::abs(error) > 0 && (motionless < time || !timeout))
      {
        error = target - Inertial.heading();
        integral += error;
        if (error <= 0) 
        {
          integral = 0;
        }
        derivative = error - prevError;
        prevError = error;
        double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
        l.spin(fwd, volts, voltageUnits::volt);
        r.spin(reverse, volts, voltageUnits::volt);
        if(dt.velocity(percentUnits::pct) == 0)
        {
          motionless+=15;
        }
        vex::task::sleep(15);
      }
      goto end;
    } 
    else if (error > 180) 
    {
      double error = target - Inertial.heading();
      double integral = error;
      double prevError = error;
      double derivative = error - prevError;
      while (std::abs(error) > 0 && (motionless < time || !timeout))
      {
        error = error = target - Inertial.heading();
        integral += error;
        if (error <= 0) 
        {
          integral = 0;
        }
        derivative = error - prevError;
        prevError = error;
        double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
        l.spin(reverse, volts, voltageUnits::volt);
        r.spin(fwd, volts, voltageUnits::volt);
        if(dt.velocity(percentUnits::pct) == 0)
        {
          motionless+=15;
        }
        vex::task::sleep(15);
      }
      goto end;
    }
  }
end:
  vex::task::sleep(20);
}


/*
void turnFor(double raw, bool timeout = false, int time = 250) 
{
  if (Inertial.installed()) 
  {
    double kP = 0.1;    //.5
    double kI = 0.0006; //.0035
    double kD = 0.022;   // 0.3
    if (raw > 0) 
    {
      double target = Inertial.rotation(rotationUnits::deg) + raw;
      double error = target - Inertial.rotation(rotationUnits::deg);
      double integral = error;
      double prevError = error;
      double derivative = error - prevError;
      int motionless = 0;
      while (std::abs(error) > 0 && (motionless < time || !timeout))
      {
        error = target - Inertial.rotation(rotationUnits::deg);
        integral += error;
        if (error <= 0) 
        {
          integral = 0;
        }
        derivative = error - prevError;
        prevError = error;
        double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
        l.spin(fwd, volts, voltageUnits::volt);
        r.spin(reverse, volts, voltageUnits::volt);
        if(dt.velocity(percentUnits::pct) == 0)
        {
          motionless+=15;
        }
        vex::task::sleep(15);
      }
      goto end;
    } 
    else if (raw < 0) 
    {
      double target = Inertial.rotation(rotationUnits::deg) + raw; //might not work
      double error = target - Inertial.rotation(rotationUnits::deg); //might not work
      double integral = error;
      double prevError = error;
      double derivative = error - prevError;
      int motionless = 0;
      while (std::abs(error) > 0 && (motionless < time || !timeout))
      {
        error = target - Inertial.rotation(rotationUnits::deg);
        integral += error;
        if (error >= 0) 
        {
          integral = 0;
        }
        derivative = error - prevError;
        prevError = error;
        double volts = std::abs(error * kP) + std::abs(integral * kI) - std::abs(derivative * kD);
        l.spin(reverse, volts, voltageUnits::volt);
        r.spin(fwd, volts, voltageUnits::volt);
        if(dt.velocity(percentUnits::pct) == 0)
        {
          motionless+=15;
        }
        vex::task::sleep(15);
      }
      goto end;
    }
  }
end:
  vex::task::sleep(20);
}
*/
// Finding kP, kI, kD notes:
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

void tiltTo(int potentiometerPCT, double volts, bool slowDown = false) 
{
  double target = potentiometerPCT; // In revolutions
  double error = target - tilt.value(percentUnits::pct);
  if (std::abs(error) == 0)
    goto end;
  while (std::abs(error) > 0 && !slowDown) 
  {
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
  int dT = 15/1000;
  if (error > 0) 
  {
    while (std::abs(error) > 0) 
    {
      error = potentiometerPCT - tilt.value(pct);
      integral += error;
      if (error <= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
      Tilt.spin(fwd, volts, voltageUnits::volt);
      vex::task::sleep(15);
    }
  }
  else if (error < 0) 
  {
    while (std::abs(error) > 0) 
    {
      error = potentiometerPCT - tilt.value(pct);
      integral += error;
      if (error >= 0) 
      {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
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
  if (lift.value(pct) > 32 && tilt.value(percentUnits::pct) < 34) 
  {
    tiltTo(34, 5);
  } 
  else if (lift.value(pct) <= 32 && tilt.value(percentUnits::pct) >= 34) 
  {
    tiltTo(tiltMin, 4);
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
  int dT = 15/1000;
  bool timeout = true;
  int time = 75;
  double error = potentiometerPCT - lift.value(pct);
  double integral = error;
  double prevError = error;
  double derivative = error - prevError;
  double kP = .55;    // 0.15
  double kI = 0.0066 / dT;    // 0.03
  double kD = 0.04 * dT;    // 0.1
  int motionless = 0;
  if (error > 0) 
  {
    while (std::abs(error) > 0 && (motionless < time || !timeout)) 
    {
      liftTiltCheck();
      error = potentiometerPCT - lift.value(pct);
      integral += error;
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
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
      liftTiltCheck();
      error = potentiometerPCT - lift.value(pct);
      integral += error;
      derivative = error - prevError;
      prevError = error;
      double volts = kP * error + kI * integral * dT + kD * (derivative / dT);
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
  tiltTo(tiltMax, 12);
  tiltTo(tiltMin, 12);
  liftTo(liftMin+12, 12);
  intake.spin(vex::forward, 100, pct);
  liftTo(liftMin);
  // drive(-.1, 60, false, false, false);
  //tiltTo(tiltMax, 12);
  //tiltTo(tiltMin, 12);
  //intake.stop();
}

void stack(void) 
{
  double target = tiltStack; // In revolutions
  double error = target - tilt.value(percentUnits::pct);
  while (error > 0) 
  {
    if(tilt.value(pct) <= 38)
    {
      intake.spin(directionType::rev, 30, percentUnits::pct);
    }
    else
      intake.stop();
    error = target - tilt.value(percentUnits::pct);
    double volts = .15 * error + 2;
    Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    vex::task::sleep(20);
  }
  intake.stop();
  Tilt.stop();
}

void tower(void) 
{
  liftTo(liftTower);
}

void fadeAway()
{
  intake.spinFor(directionType::rev, -2, rotationUnits::rev, 35, velocityUnits::pct, false);
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
  le.setPosition(0, rotationUnits::rev);
  re.setPosition(0, rotationUnits::rev);
}
/*
void cGUI ()
{
  start:
  int row = 1;
  int cursor = 1;
  std::string dialog[] =  {"Side: R|B", "Test: Y|N", "Ambi: Y|N", "Manual: Y|N",
"Record: Y|N", "Play: Y|N"}; std::string modularManual[] =  {"Side: R|B", "Test:
Y|N", "Ambi: Y|N", "Manual: Y|N", "Record: Y|N", "Play: Y|N"};
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(row, 1);
  Controller1.Screen.print(dialog[row]);
  row++;
  Controller1.Screen.setCursor(row, 1);
  Controller1.Screen.print("Test: Y|N");
  row++;
  Controller1.Screen.setCursor(row, 1);
  Controller1.Screen.print("Ambi: Y|N");
  Controller1.Screen.print("Manual: Y|N");
  Controller1.Screen.print("Record: Y|N");
  Controller1.Screen.print("Play: Y|N");
  Controller1.Screen.print("Manual: >Y|N");
  while(1)
  {
    while((Controller1.ButtonUp.pressing() || Controller1.Axis3.value() > 20) &&
cursor >= 3)
    {
      cursor++;
      vex::task::sleep(200);
    }

    while((Controller1.ButtonDown.pressing() || Controller1.Axis3.value() < -20)
&& cursor > 1)
    {
      cursor--;
      vex::task::sleep(200);
    }

    if(Controller1.ButtonRight.pressing() || Controller1.Axis1.value() > 20)
    {

    }

    if(Controller1.ButtonLeft.pressing() || Controller1.Axis1.value() < -20)
    {
      Controller1.Screen.print("Manual: >Y|N");
    }

    if(Controller1.ButtonA.pressing())
    {

      autonBrain();
      autonController();
      break;
    }
  }
}
*/
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

// Sine drive
/*
void drive(double rev, int maxVel = 80, bool pidOn = true, bool correct = true,
bool waitForCompletion = false)
{
    if(waitForCompletion)
    {
      pidOn = false;
    }
    if(!pidOn)
    {
      d.spinFor(directionType::fwd, rev, rotationUnits::rev, maxVel,
velocityUnits::pct, waitForCompletion); goto end;
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
*/

#endif