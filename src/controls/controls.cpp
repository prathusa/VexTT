#include "main.h"
using namespace vex;
using namespace std;
bool isY = false;
bool isX = false;
bool isLA = false;
double liftHold = liftMin;
calc::Slew driveSlew(2, 24);

void controls() 
{
  // Mech Split-Arcade Control
  
  double forward = Controller1.Axis3.position(vex::percent)/(driveSpeedFactor);
  double strafe = Controller1.Axis4.position(vex::percent)/(driveSpeedFactor);
  double turn = Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor);

  // Linear Analog Control

  forward = 1.2*Controller1.Axis3.position(vex::percent)/(driveSpeedFactor*10);
  strafe = 1.2*Controller1.Axis4.position(vex::percent)/(driveSpeedFactor*10);
  turn = 1.2*Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor*10);

  double line_LFM = (forward + strafe + turn);
  double line_LRM = (forward - strafe + turn);
  double line_RFM = (forward - strafe - turn);
  double line_RRM = (forward + strafe - turn);

  // Reverse Deadzone Linear Control

  if(forward > 0)
    forward = 0.105 * Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) + 1.5;
  else if(forward < 0)
    forward = 0.105 * Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) - 1.5;
  else 
    forward = 0;

  if(strafe > 0)
    strafe = 0.105 * Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) + 1.5;
  else if(strafe < 0)
    strafe = 0.105 * Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) - 1.5;
  else 
    strafe = 0;

  if(turn > 0)
    turn = 0.1 * Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) + 2.0;
  else if(turn < 0)
    turn = 0.1 * Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) - 2.0;
  else 
    turn = 0;

  double rlin_LFM = (forward + strafe + turn);
  double rlin_LRM = (forward - strafe + turn);
  double rlin_RFM = (forward - strafe - turn);
  double rlin_RRM = (forward + strafe - turn);

  // Reverse Deadzone Exponential Analog Control
  if(forward > 0)
    forward = 0.00105 * abs(Controller1.Axis3.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) + 1.5;
  else if(forward < 0)
    forward = 0.00105 * abs(Controller1.Axis3.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis3.position(vex::percent)/(driveSpeedFactor) - 1.5;
  else 
    forward = 0;

  if(strafe > 0)
    strafe = 0.00105 * abs(Controller1.Axis4.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) + 1.5;
  else if(strafe < 0)
    strafe = 0.00105 * abs(Controller1.Axis4.position(vex::percent)/(driveSpeedFactor))*Controller1.Axis4.position(vex::percent)/(driveSpeedFactor) - 1.5;
  else 
    strafe = 0;

  if(turn > 0)
    turn = 0.001 * abs(Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor))*Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) + 2.0;
  else if(turn < 0)
    turn = 0.001 * abs(Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor))*Controller1.Axis1.position(vex::percent)/(driveSpeedFactor*turnSpeedFactor) - 2.0;
  else 
    turn = 0;

  double expo_LFM = (forward + strafe + turn);
  double expo_LRM = (forward - strafe + turn);
  double expo_RFM = (forward - strafe - turn);
  double expo_RRM = (forward + strafe - turn);
  
  // Slewed Acceleration, changing the first parameter changes the style of  

  double slew_LFM = driveSlew.slew(rlin_LFM, LeftFrontMotor.velocity(percentUnits::pct)/10.0);
  double slew_LRM = driveSlew.slew(rlin_LRM, LeftRearMotor.velocity(percentUnits::pct)/10.0);
  double slew_RFM = driveSlew.slew(rlin_RFM, RightFrontMotor.velocity(percentUnits::pct)/10.0);
  double slew_RRM = driveSlew.slew(rlin_RRM, RightRearMotor.velocity(percentUnits::pct)/10.0);

  // Motor Spin Function, Change the middle parameter variable to change the type of drive acceleration/control

  /*
  LeftFrontMotor.spin(vex::forward, line_LFM, vex::volt);
  LeftRearMotor.spin(vex::forward, line_LRM, vex::volt);
  RightFrontMotor.spin(vex::forward, line_RFM, vex::volt);
  RightRearMotor.spin(vex::forward, line_RRM, vex::volt);
  */

  LeftFrontMotor.spin(vex::forward, rlin_LFM, vex::volt);
  LeftRearMotor.spin(vex::forward, rlin_LRM, vex::volt);
  RightFrontMotor.spin(vex::forward, rlin_RFM, vex::volt);
  RightRearMotor.spin(vex::forward, rlin_RRM, vex::volt);

  /*
  LeftFrontMotor.spin(vex::forward, expo_LFM, vex::volt);
  LeftRearMotor.spin(vex::forward, expo_LRM, vex::volt);
  RightFrontMotor.spin(vex::forward, expo_RFM, vex::volt);
  RightRearMotor.spin(vex::forward, expo_RRM, vex::volt);
  */
  /*
  LeftFrontMotor.spin(vex::forward, slew_LFM, vex::volt);
  LeftRearMotor.spin(vex::forward, slew_LRM, vex::volt);
  RightFrontMotor.spin(vex::forward, slew_RFM, vex::volt);
  RightRearMotor.spin(vex::forward, slew_RRM, vex::volt);
  */

  LeftFrontMotor.setBrake(coast);
  RightFrontMotor.setBrake(coast);
  LeftRearMotor.setBrake(coast);
  RightRearMotor.setBrake(coast);

  // if (lift.value(pct) >= liftTowerLow - 2) 
  //   turnSpeedFactor = 1.3;
  // else
  //   turnSpeedFactor = 1;

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

  // // -----------------------------Intake Control
  // if (Controller1.ButtonL1.pressing() && lift.value(percentUnits::pct) < liftTowerLow-2) 
  // {
  //   intake.spin(directionType::fwd, 40, pct);
  // }
  // else if (Controller1.ButtonL2.pressing() && lift.value(pct) < liftTowerMid) 
  // {
  //   intake.spin(directionType::rev, 100, pct);
  // } 
  // // else if(isStacking)
  // // {
  // //   LeftIntake.stop(brakeType::coast);
  // //   RightIntake.stop(brakeType::coast);
  // // }
  // else
  // {
  //   LeftIntake.stop(brakeType::brake);
  //   RightIntake.stop(brakeType::brake);
  // }

  // // -----------------------------Tilt Control
  // if(Controller1.ButtonR2.pressing() && tilt.value(percentUnits::pct) < tiltMax) 
  // {
  //   isY = false;
  //   double target = tiltStack; // In revolutions
  //   double error = target - tilt.value(percentUnits::pct);
  //   if (error > 0) 
  //   {
  //     error = target - tilt.value(percentUnits::pct);
  //     double volts = .4 * error + 3;
  //     Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
  //     vex::task::sleep(20);
  //   } 
  //   else 
  //   {
  //     error = 0;
  //     double volts = error + 3;
  //     Tilt.spin(directionType::fwd, volts, voltageUnits::volt);
  //   }
  // }
  // else if(Controller1.ButtonR1.pressing() && tilt.value(percentUnits::pct) > tiltMin) 
  // {
  //   isY = false;
  //   double target = tiltMax; // In revolutions
  //   double error = target - tilt.value(percentUnits::pct);
  //   if (error > 0) 
  //   {
  //     error = target - tilt.value(percentUnits::pct);
  //     double volts = .4 * error + 3;
  //     Tilt.spin(directionType::rev, volts, voltageUnits::volt);
  //     vex::task::sleep(20);
  //   } 
  //   else 
  //   {
  //     error = 0;
  //     double volts = error + 3;
  //     Tilt.spin(directionType::rev, volts, voltageUnits::volt);
  //   }
  // }
  // else if (Controller1.ButtonY.pressing() && tilt.value(pct) < tiltStack - 2) 
  // {
  //   isY = true;
  // } 
  // else if (Controller1.ButtonY.pressing() && tilt.value(pct) >= tiltStack - 2) 
  // {
  //   isY = true;
  // }
  // else if(!isY)
  //   Tilt.stop(hold);

  
  // // if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  // // {
  // //   Tilt.spin(fwd, 100, pct);
  // // }
  // // else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  // // {
  // //   Tilt.spin(directionType::rev, 100, pct);
  // // }
  // // else 
  // //   Tilt.stop(hold);
  
  // // -----------------------------Lift Control

  // if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  // {
  //   isLA = false;
  //   Lift.spin(fwd, 100, pct);
  //   if(lift.value(pct) > liftHold)
  //     liftHold = lift.value(pct);
  // }
  // else if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerLow) 
  // {
  //   isLA = true;
  //   robot.lifter.aTo(liftTowerLow);
  // } 
  // else if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerMid) 
  // {
  //   isLA = true;
  //   robot.lifter.aTo(liftTowerMid);
  // }
  // else if (Controller1.ButtonLeft.pressing() && lift.value(pct) >= liftTowerMid)
  // {
  //   isLA = true;
  //   robot.lifter.aTo(liftMin);
  // }
  // else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  // {
  //   isLA = false;
  //   Lift.spin(directionType::rev, 100, pct);
  //   if(lift.value(pct) < liftHold)
  //     liftHold = lift.value(pct);
  // }
  // else if(!isLA)
  // {
  //   robot.lifter.aTo(liftHold);
  // }

  // // if(Controller1.ButtonUp.pressing() && lift.value(pct) < liftMax)
  // //   Lift.spin(fwd, 100, pct);
  // // else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
  // //   Lift.spin(directionType::rev, 100, pct);
  // // else 
  // //   Lift.stop(hold);

  // // -----------------------------Complete Autostack and Fadeaway Macro

  //   if (Controller1.ButtonX.pressing()) 
  //   {
  //     // flipout();
  //     intake.spinFor(fwd, 1, rotationUnits::rev, 50, velocityUnits::pct);
  //     d.spinFor(fwd, -1, rotationUnits::rev, 50, velocityUnits::pct);
  //   }

  //   // -----------------------------Stack Macro

    
  
}