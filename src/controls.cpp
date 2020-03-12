#include "vex.h"
using namespace vex;
using namespace std;
bool isY = false;
bool isX = false;
bool isLA = false;
double liftHold = liftMin;

void controls() 
{
  // Mech Split-Arcade Control
  int forward = Controller1.Axis3.position(vex::percent)/(driveSpeedFactor);
  int strafe = Controller1.Axis4.position(vex::percent)/(driveSpeedFactor);
  int turn = Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor);
  
  // Exponential Driver Control
  if(forward > 0)
    forward = 0.0085 * abs(Controller1.Axis3.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) + 15;
  else if(forward < 0)
    forward = 0.0085 * abs(Controller1.Axis3.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) - 15;
  else 
    forward = 0;

  if(strafe > 0)
    strafe = 0.0085 * abs(Controller1.Axis4.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) + 15;
  else if(strafe < 0)
    strafe = 0.0085 * abs(Controller1.Axis4.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) - 15;
  else 
    strafe = 0;

  if(turn > 0)
    turn = 0.008 * abs(Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor))*Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) + 20;
  else if(turn < 0)
    turn = 0.008 * abs(Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor))*Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) - 20;
  else 
    turn = 0;

  // Slew Control Drive
  LeftFrontMotor.spin(vex::forward, (forward + strafe + turn), vex::percent);
  LeftRearMotor.spin(vex::forward, (forward - strafe + turn), vex::percent);
  RightFrontMotor.spin(vex::forward, (forward - strafe - turn), vex::percent);
  RightRearMotor.spin(vex::forward, (forward + strafe - turn), vex::percent);

  LeftFrontMotor.setBrake(coast);
  RightFrontMotor.setBrake(coast);
  LeftRearMotor.setBrake(coast);
  RightRearMotor.setBrake(coast);

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
  else if (Controller1.ButtonL2.pressing() && lift.value(pct) < liftTowerMid) 
  {
    intake.spin(directionType::rev, 100, pct);
  } 
  // else if(isStacking)
  // {
  //   LeftIntake.stop(brakeType::coast);
  //   RightIntake.stop(brakeType::coast);
  // }
  else
  {
    LeftIntake.stop(brakeType::brake);
    RightIntake.stop(brakeType::brake);
  }

  // -----------------------------Tilt Control
  if(Controller1.ButtonR2.pressing() && tilt.value(percentUnits::pct) < tiltMax) 
  {
    isY = false;
    double target = tiltStack; // In revolutions
    double error = target - tilt.value(percentUnits::pct);
    if (error > 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      double volts = .4 * error + 3;
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
  else if(Controller1.ButtonR1.pressing() && tilt.value(percentUnits::pct) > tiltMin) 
  {
    isY = false;
    double target = tiltMax; // In revolutions
    double error = target - tilt.value(percentUnits::pct);
    if (error > 0) 
    {
      error = target - tilt.value(percentUnits::pct);
      double volts = .4 * error + 3;
      Tilt.spin(directionType::rev, volts, voltageUnits::volt);
      vex::task::sleep(20);
    } 
    else 
    {
      error = 0;
      double volts = error + 3;
      Tilt.spin(directionType::rev, volts, voltageUnits::volt);
    }
  }
  else if (Controller1.ButtonY.pressing() && tilt.value(pct) < tiltStack - 2) 
  {
    isY = true;
    robot.tilter.aStack();
  } 
  else if (Controller1.ButtonY.pressing() && tilt.value(pct) >= tiltStack - 2) 
  {
    isY = true;
    robot.tilter.aTo(tiltMin);
  }
  else if(!isY)
    Tilt.stop(hold);

  
  // if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  // {
  //   Tilt.spin(fwd, 100, pct);
  // }
  // else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  // {
  //   Tilt.spin(directionType::rev, 100, pct);
  // }
  // else 
  //   Tilt.stop(hold);
  
  // -----------------------------Lift Control

  if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  {
    isLA = false;
    Lift.spin(fwd, 100, pct);
    if(lift.value(pct) > liftHold)
      liftHold = lift.value(pct);
  }
  else if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerLow) 
  {
    isLA = true;
    robot.lifter.aTo(liftTowerLow);
  } 
  else if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerMid) 
  {
    isLA = true;
    robot.lifter.aTo(liftTowerMid);
  }
  else if (Controller1.ButtonLeft.pressing() && lift.value(pct) >= liftTowerMid)
  {
    isLA = true;
    robot.lifter.aTo(liftMin);
  }
  else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  {
    isLA = false;
    Lift.spin(directionType::rev, 100, pct);
    if(lift.value(pct) < liftHold)
      liftHold = lift.value(pct);
  }
  else if(!isLA)
  {
    robot.lifter.aTo(liftHold);
  }

  // if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  //   Lift.spin(fwd, 100, pct);
  // else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  //   Lift.spin(directionType::rev, 100, pct);
  // else 
  //   Lift.stop(hold);

  // -----------------------------Complete Autostack and Fadeaway Macro

    if (Controller1.ButtonX.pressing()) 
    {
      // flipout();
      robot.tilter.Stack();
      intake.spinFor(fwd, 1, rotationUnits::rev, 50, velocityUnits::pct);
      d.spinFor(fwd, -1, rotationUnits::rev, 50, velocityUnits::pct);
    }

    // -----------------------------Stack Macro

    
  
}