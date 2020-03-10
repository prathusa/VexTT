#include "vex.h"

void usercontrol(void) 
{
  while (1) 
  {
    controls();

    // -----------------------------Complete Autostack and Fadeaway Macro

    if (Controller1.ButtonX.pressing()) 
    {
      robot.tilter.setTilt();
      robot.tilter.To(tiltStack);
      d.spinFor(fwd, -1, rotationUnits::rev, 40, velocityUnits::pct);
      intake.spinFor(fwd, 1, rotationUnits::rev, 40, velocityUnits::pct);
    }

    // -----------------------------Stack Macro

    if (Controller1.ButtonY.pressing() && tilt.value(pct) < tiltStack - 2) 
    {
      robot.tilter.setTilt();
      robot.tilter.aTo(tiltStack);
    } 
    else if (Controller1.ButtonY.pressing() && tilt.value(pct) >= tiltStack - 2) 
    {
      robot.tilter.setTilt();
      robot.tilter.aTo(tiltMin);
    }

    // -----------------------------Lift Macros

    if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerLow) 
    {
      robot.lifter.setLift();
      robot.lifter.aTo(liftTowerLow);
      Lift.setBrake(hold);
    } 
    else if (Controller1.ButtonLeft.pressing() && lift.value(pct) < liftTowerMid) 
    {
      robot.lifter.setLift();
      robot.lifter.aTo(liftTowerMid);
      Lift.setBrake(hold);
    }
    else if (Controller1.ButtonLeft.pressing() && lift.value(pct) >= liftTowerMid)
    {
      robot.lifter.setLift();
      robot.lifter.aTo(liftMin);
      Lift.setBrake(hold);
    }
  }
}