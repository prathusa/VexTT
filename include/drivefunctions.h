#pragma once

void turnTo(double raw, int intakeSpeed, int timeout = 14);
void marginalTurnTo(double raw, int intakeSpeed, double marginOfError = 1.0);
void turn(double raw, int intakeSpeed = 0, int timeout = 1, double marginOfError = 1.0);
void turnFor(double raw, bool timeout = false, int time = 250);
void turnToHeading(double target, int timeout = 250);

void tiltTo(int potentiometerPCT, double volts, bool slowDown = false);
void tiltFor(int potentiometerPCT, double volts);
void tiltTo(int potentiometerPCT);
void tiltFor(int potentiometerPCT);

void liftTiltCheck();

void tiltIntakeCheck();

void liftTo(int potentiometerPCT, double volts);
void liftFor(int potentiometerPCT, double volts);
void liftTo(int potentiometerPCT);
void liftFor(int potentiometerPCT);

void flipOut();

void stack(int intakeSpeed = 0);

void towerLow(void);
void towerMid(void);

void fadeAway();
void fadeAwayMid();

// Added Controller and Brain feedback when autonomous is selected.
void autonController();
void autonBrain();

void resetEncoders(void);

void driveTo(double positionRev, int intakeSpeed = 0, int timeout = 50, double kP = 2, double kI = 0.0075, double kD = 6);
void driveFor(double positionRev, int driveSpeed = 50, int intakeSpeed = 0, int timeout = 50);
void drive(double revolutions, int intakeSpeed = 0, int timeout = 50, double kP = 2, double kI = 0.0095, double kD = 6);

void pTurn(double degrees);

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
