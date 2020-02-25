#include "vex.h"
using namespace vex;

void controls() 
{
  // Mech Split-Arcade Control
  int forward = Controller1.Axis3.position(vex::percent)/(driveSpeedFactor);
  int sideways = Controller1.Axis4.position(vex::percent)/(driveSpeedFactor);
  int turn = -Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor);
  
  // Combined Exponential Drive Curve with Slew Curve modeling
  LeftFrontMotor.spin(vex::forward, driveSlew(0.01 * pow(forward + sideways - turn, 2)), vex::percent);
  LeftRearMotor.spin(vex::forward, driveSlew(0.01 * pow(forward - sideways - turn, 2)), vex::percent);
  RightFrontMotor.spin(vex::forward, driveSlew(0.01 * pow(forward - sideways + turn, 2)), vex::percent);
  RightRearMotor.spin(vex::forward, driveSlew(0.01 * pow(forward + sideways + turn, 2)), vex::percent);

  /*
  // Exponential Driver Control
  LeftFrontMotor.spin(vex::forward, 0.01 * pow(forward + sideways - turn, 2), vex::percent);
  LeftRearMotor.spin(vex::forward, 0.01 * pow(forward - sideways - turn, 2), vex::percent);
  RightFrontMotor.spin(vex::forward, 0.01 * pow(forward - sideways + turn, 2), vex::percent);
  RightRearMotor.spin(vex::forward, 0.01 * pow(forward + sideways + turn, 2), vex::percent);

  // Slew Control Drive
  LeftFrontMotor.spin(vex::forward, driveSlew(forward + sideways - turn), vex::percent);
  LeftRearMotor.spin(vex::forward, driveSlew(forward - sideways - turn), vex::percent);
  RightFrontMotor.spin(vex::forward, driveSlew(forward - sideways + turn), vex::percent);
  RightRearMotor.spin(vex::forward, driveSlew(forward + sideways + turn), vex::percent);

  // Vanilla Drive Code
  LeftFrontMotor.spin(vex::forward, driveSlew(forward + sideways - turn), vex::percent);
  LeftRearMotor.spin(vex::forward, driveSlew(forward - sideways - turn), vex::percent);
  RightFrontMotor.spin(vex::forward, driveSlew(forward - sideways + turn), vex::percent);
  RightRearMotor.spin(vex::forward, driveSlew(forward + sideways + turn), vex::percent);
  */

  LeftFrontMotor.setBrake(coast);
  RightFrontMotor.setBrake(coast);
  LeftRearMotor.setBrake(coast);
  RightRearMotor.setBrake(coast);
  
  /*
  // Regular Split-Arcade Control
  LeftFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value() * turnSpeedFactor) / (driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
  LeftRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value() * turnSpeedFactor) / (driveSpeedFactor), velocityUnits::pct); //(Axis3+Axis4)/2;
  RightFrontMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value() * turnSpeedFactor) / (driveSpeedFactor), velocityUnits::pct); //(Axis3-Axis4)/2;
  RightRearMotor.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value() * turnSpeedFactor) / (driveSpeedFactor), velocityUnits::pct); //(Axis3-Axis4)/2;

  // Tank Control
  LeftFrontMotor.spin(vex::directionType::fwd,Controller1.Axis3.value() / driveSpeedFactor,vex::velocityUnits::pct);
  RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value() / driveSpeedFactor, vex::velocityUnits::pct);
  RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value() / driveSpeedFactor, vex::velocityUnits::pct);
  LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value() / driveSpeedFactor, vex::velocityUnits::pct);
   */

  if (lift.value(pct) >= liftTowerLow - 2) 
    turnSpeedFactor = 1.3;
  else
    turnSpeedFactor = 1;

  //------------------------------DriveSpeed Control
  if (Controller1.ButtonB.pressing())
  {
    driveSpeedFactor = 1.5; // Makes robot slower
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Slow Mode");
    Controller1.rumble("-");
  } 
  else if (Controller1.ButtonA.pressing()) 
  {
    driveSpeedFactor = 1;
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Full Speed");
    Controller1.rumble(".");
  }

  // -----------------------------Intake Control
  if (Controller1.ButtonL1.pressing() && lift.value(percentUnits::pct) < liftTowerLow-2) 
  {
    intake.spin(directionType::fwd, 40, pct);
  } 
  //else if (Controller1.ButtonL1.pressing() && lift.value(percentUnits::pct) > liftTowerLow-2 && lift.value(percentUnits::pct) < liftTowerMid-2) 
  //{
  //  intake.spin(directionType::fwd, 40, pct);
  //} 
  //else if (Controller1.ButtonL1.pressing() && lift.value(percentUnits::pct) > liftTowerMid-2) 
  //{
  //  intake.spin(directionType::fwd, 40, pct);
  //} 
  else if (Controller1.ButtonL2.pressing() && lift.value(pct) < liftTowerMid) 
  {
    intake.spin(directionType::rev, 100, pct);
  } 
  else if(isStacking)
  {
    LeftIntake.stop(brakeType::coast);
    RightIntake.stop(brakeType::coast);
  }
  else
  {
    LeftIntake.stop(brakeType::brake);
    RightIntake.stop(brakeType::brake);
  }

  // -----------------------------Tilt Control
  if (Controller1.ButtonR2.pressing() && tilt.value(percentUnits::pct) < tiltMax && lift.value(pct) < liftTowerLow) 
  {
    double target = tiltStack; // In revolutions
    double error = target - tilt.value(percentUnits::pct);
    if (error > 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      double volts = .4 * error + 2.5;
      Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
      vex::task::sleep(20);
    } 
    else 
    {
      error = 0;
      double volts = error + 2.5;
      Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
    }
  } 
  else if (Controller1.ButtonR1.pressing() && tilt.value(percentUnits::pct) > tiltMin && lift.value(pct) < liftTowerLow) 
  {
    double target = tiltMax; // In revolutions
    double error = target - tilt.value(percentUnits::pct);
    if (error > 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      double volts = .4 * error + 2.5;
      Tilt.spin(directionType::rev, volts, voltageUnits::volt);
      vex::task::sleep(20);
    } 
    else 
    {
      error = 0;
      double volts = error + 2.5;
      Tilt.spin(directionType::rev, volts, voltageUnits::volt);
    }
  } 
  else 
    Tilt.stop(hold);
}