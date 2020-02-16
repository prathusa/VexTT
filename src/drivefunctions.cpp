#include "vex.h"

BASE_DRIVE::BASE_DRIVE(){};
IMU::IMU(){};
mech::MECH_DRIVE::MECH_DRIVE(){};
LIFTER::LIFTER(){};
TILTER::TILTER(){};
bot::ROBOT::ROBOT(){};

IMU imu;
void IMU::turnTo(double raw, int intakeSpeed, int timeout)
{
  if (Inertial.installed()) 
  {
    double kP = 0.45;    // 0.45
    double kI = 0.00006; // 0.00006
    double kD = 0.50;    // 0.45
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
  else
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("No Inertial Sensor Installed");
  }
end:
  vex::task::sleep(20);
}

void marginalTurnTo(double raw, int intakeSpeed, double marginOfError)
{
  if (Inertial.installed()) 
  {
    double kP = 0.45;    // 0.45
    double kI = 0.0006; // 0.00006
    double kD = 0.50;    // 0.45
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
  else
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("No Inertial Sensor Installed");
  }
end:
  vex::task::sleep(20);
}

void BASE_DRIVE::turn(double raw, int intakeSpeed, int timeout, double marginOfError)
{
	//ROBOT.timeOut(2.5);
	//ROBOT.reset();

	if (os.getValues(COLOR) == BLUE) //If color is 0 (BLUE) flip the values 
		raw = -raw;

  if(timeout == 0)
    marginalTurnTo(raw, intakeSpeed, marginOfError);
  else
	  imu.turnTo(raw, intakeSpeed, timeout);
}

void turnFor(double raw, bool timeout, int time) 
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
void IMU::turnToHeading(double target, int timeout) 
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

void TILTER::tiltTo(int potentiometerPCT, double volts, bool slowDown) 
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

void TILTER::tiltFor(int potentiometerPCT, double volts) 
{
  int start = tilt.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  robot.tiltTo(target, volts);
}

void TILTER::tiltTo(int potentiometerPCT) 
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

void TILTER::tiltFor(int potentiometerPCT) 
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
  if (lift.value(pct) > 32 && tilt.value(percentUnits::pct) < 37) 
  {
    robot.tiltTo(37, 12);
  } 
  else if (lift.value(pct) <= 32 && tilt.value(percentUnits::pct) >= 37) 
  {
    robot.tiltTo(tiltMin, 12);
  }
}

void tiltIntakeCheck()
{
  if(tilt.value(percentUnits::pct) > 40)
  {
    LeftIntake.setBrake(coast);
    RightIntake.setBrake(coast);
  }
}

void LIFTER::liftTo(int potentiometerPCT, double volts) 
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

void LIFTER::liftFor(int potentiometerPCT, double volts) 
{
  int start = lift.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  liftTo(target, volts);
}

void LIFTER::liftTo(int potentiometerPCT) 
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

void LIFTER::liftFor(int potentiometerPCT) 
{
  int start = lift.value(pct);
  int distance = potentiometerPCT;
  double target = distance + start;
  liftTo(target);
}


void bot::ROBOT::flipOut() 
{
  liftTo(liftTowerLow-5, 12);
  //vex::task::sleep(200);
  liftTo(liftMin, 12);
  //vex::task::sleep(500);
}

void TILTER::stack(int intakeSpeed) 
{
  double target = tiltStack; // In revolutions
  double error = target - tilt.value(percentUnits::pct);
  while (error > 0) 
  {
    isStacking = true;
    intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
    tiltIntakeCheck();
    controls();
    error = target - tilt.value(percentUnits::pct);
    double volts = .4 * error + 2.5; //.15 * error + 2; //.2 * error + 2 (2.550s)
    Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    vex::task::sleep(20);
  }
  isStacking = false;
  intake.stop();
  Tilt.stop();
}

void LIFTER::towerLow(void) 
{
  liftTo(liftTowerLow, 12);
}

void LIFTER::towerMid(void) 
{
  liftTo(liftTowerMid, 12);
}

void bot::ROBOT::fadeAway()
{
  intake.spinFor(directionType::rev, -2, rotationUnits::rev, 35, velocityUnits::pct, false); //possible reduction needed
  d.spinFor(-.75, rotationUnits::rev, 30, velocityUnits::pct);
}

void bot::ROBOT::fadeAwayMid()
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

void bot::ROBOT::resetEncoders(void) 
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

void BASE_DRIVE::driveTo(double positionRev, int intakeSpeed, int timeout, double kP, double kI, double kD) 
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

void BASE_DRIVE::driveFor(double positionRev, int driveSpeed, int intakeSpeed, int timeout) 
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

void BASE_DRIVE::drive(double revolutions, int intakeSpeed, int timeout, double kP, double kI, double kD) 
{
  double target = revolutions + d.position(rotationUnits::rev);
  driveTo(target, intakeSpeed, timeout, kP, kI, kD);
}

void mech::MECH_DRIVE::strafeTo(double revolutions, int intakeSpeed, int timeout, double kP, double kI, double kD) 
{
  double errorLD = revolutions - ld.position(rotationUnits::rev);
  double errorRD = -revolutions - rd.position(rotationUnits::rev);
  double integralLD = errorLD;
  double integralRD = errorRD;
  double prevErrorLD = errorLD;
  double prevErrorRD = errorRD;
  double derivativeLD = errorLD - prevErrorLD;
  double derivativeRD = errorRD - prevErrorRD;
  int motionless = 0;
  if (errorLD > 0 && errorRD < 0) 
  {
    while (errorLD > 0 && errorRD < 0 && motionless <= timeout) 
    {
      intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      errorLD = revolutions - ld.position(rotationUnits::rev);
      errorRD = -revolutions - rd.position(rotationUnits::rev);
      integralLD += errorLD;
      integralRD += errorRD;
      if (errorLD <= 0 || errorRD >= 0) 
      {
        integralLD = 0;
        integralRD = 0;
      }
      derivativeLD = errorLD - prevErrorLD;
      derivativeRD = errorLD - prevErrorLD;
      prevErrorLD = errorLD;
      prevErrorLD = errorLD;
      double voltsLD = errorLD * kP + integralLD * kI + derivativeLD * kD;
      double voltsRD = errorRD * kP + integralRD * kI + derivativeRD * kD;
      ld.spin(fwd, voltsLD, voltageUnits::volt);
      rd.spin(fwd, voltsRD, voltageUnits::volt);
      if(std::abs(dt.velocity(percentUnits::pct)) < 0.1)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
  }
  else if (errorLD < 0 && errorRD > 0) 
  {
    while (errorLD < 0 && errorRD > 0 && motionless <= timeout) 
    {
      intake.spin(directionType::rev, intakeSpeed, percentUnits::pct);
      errorLD = revolutions - ld.position(rotationUnits::rev);
      errorRD = -revolutions - rd.position(rotationUnits::rev);
      integralLD += errorLD;
      integralRD += errorRD;
      if (errorLD >= 0 || errorRD <= 0) 
      {
        integralLD = 0;
        integralRD = 0;
      }
      derivativeLD = errorLD - prevErrorLD;
      derivativeRD = errorLD - prevErrorLD;
      prevErrorLD = errorLD;
      prevErrorLD = errorLD;
      double voltsLD = errorLD * kP + integralLD * kI + derivativeLD * kD;
      double voltsRD = errorRD * kP + integralRD * kI + derivativeRD * kD;
      ld.spin(fwd, voltsLD, voltageUnits::volt);
      rd.spin(fwd, voltsRD, voltageUnits::volt);
      if(std::abs(dt.velocity(percentUnits::pct)) < 0.1)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
  }
  intake.stop();
}

void mech::MECH_DRIVE::strafeFor(double revolutions, int driveSpeed, int intakeSpeed, int timeout) 
{
  double error = revolutions - d.position(rotationUnits::rev);
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
      error = revolutions - d.position(rotationUnits::rev);
      double volts = (error * kP) + 2;
      ld.spin(fwd, volts, voltageUnits::volt);
      rd.spin(fwd, -volts, voltageUnits::volt);
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
      error = revolutions - d.position(rotationUnits::rev);
      double volts = (error * kP) - 2;
      ld.spin(fwd, -volts, voltageUnits::volt);
      rd.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=15;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(15);
    }
  }
  intake.stop();
}

void mech::MECH_DRIVE::strafe(double revolutions, int intakeSpeed, int timeout, double kP, double kI, double kD) 
{
  if (os.getValues(COLOR) == BLUE) //If color is 0 (BLUE) flip the values 
		revolutions = -revolutions;
  double target = revolutions + ld.position(rotationUnits::rev);
  strafeTo(target, intakeSpeed, timeout, kP, kI, kD);
}

void pTurn(double degrees) //P loop turn code (better than the smartdrive methods once kP is tuned properly)
{
  if(Inertial.installed())
  {
    double target = degrees; // In revolutions
    double error = target - Inertial.rotation();
    double kP = .6;
    if(error > 0)
    {
      
      while (std::abs(error) > 1) //1 allows +- 1 degree variance, don't change unless you know what you are doing
      {
        error = target - Inertial.rotation();
        double percent = kP * error + 15;
        l.spin(directionType::fwd, percent, pct);
	      r.spin(directionType::rev, percent, pct);
        vex::task::sleep(20);
      }
    }
    else if(error > 0)
    {
      double target = degrees; // In revolutions
      double error = target - Inertial.rotation();
      double kP = .6;
      while (std::abs(error) > 1) //1 allows +- 1 degree variance, don't change unless you know what you are doing
      {
        error = target - Inertial.rotation();
        double percent = kP * error - 15;
        l.spin(directionType::fwd, percent, pct);
	      r.spin(directionType::rev, percent, pct);
        vex::task::sleep(20);
      }
    }
    else
    {
      l.stop();
      r.stop();
      goto end;
    }
  }
  else
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("No Inertial Sensor Installed");
  }
  end:
  vex::task::sleep(10);
}

bool bot::ROBOT::allInstalled()
{
  if(Lift.installed() && Tilt.installed() && LeftFrontMotor.installed() && LeftRearMotor.installed() && RightFrontMotor.installed() && RightRearMotor.installed() && LeftIntake.installed() && RightIntake.installed())
  {
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine(1);
    Controller1.Screen.print("PORT DC");
    return true;
  }
  return false;
}

bool bot::ROBOT::driveInstalled()
{
  if(LeftFrontMotor.installed() && LeftRearMotor.installed() && RightFrontMotor.installed() && RightRearMotor.installed())
  {
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine(1);
    Controller1.Screen.print("DRIVE WORKING");
    return true;
  }
  return false;
}

void IMU::getPositionY()
{  
  double velocityY = 0;
  double positionY = 0;
  while(1)
  {
    double accelerationY = Inertial.acceleration(axisType::yaxis);
    
    velocityY += accelerationY*(0.02);
    
    positionY += velocityY*(0.02);

    std::cout << positionY << std::endl;
    task::sleep(200);
  }
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
