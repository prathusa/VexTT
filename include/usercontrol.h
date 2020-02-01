#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "vex.h"
#include "controls.h"
#include "autonomous.h"
#include "drivefunctions.h"

void usercontrol(void) 
{
    while(1) 
    {
        controls();
        
        // -----------------------------Toggle Stacker Command
        if(Controller1.ButtonY.pressing() && lift.value(pct) < liftTilter)
        {
          Brain.Timer.reset();
          stack();
          Tilt.stop(brake);
          Controller1.rumble("..");
          Controller1.Screen.clearLine(3);
          Controller1.Screen.setCursor(3, 1);
          Controller1.Screen.print("%d ", Brain.Timer.time()); 
        }
        if(Controller1.ButtonY.pressing() && tilt.value(percentUnits::pct) >= tiltStack - 2 && lift.value(pct) < liftTilter)
        {
          tiltTo(tiltMin, 12);
        }

        //Fade away
        if(Controller1.ButtonX.pressing() && lift.value(percentUnits::pct) <= liftTowerLow+2)
        {
          fadeAway();
        }
        if(Controller1.ButtonX.pressing() && std::abs(lift.value(percentUnits::pct) - liftTowerMid) <= 2)
        {
          fadeAwayMid();
        }
        
        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 100, velocityUnits::pct);
            liftTiltCheck();
        }
        else if(Controller1.ButtonDown.pressing() && lift.value(pct) > liftMin)
        {
            Lift.spin(directionType::rev, 100, velocityUnits::pct);
            liftTiltCheck();
        }
        else
        {
            Lift.setBrake(hold); //potentially make a custom hold function for the lift using potentiometer
            Lift.stop();
        }

        // -----------------------------Toggle Lift Positions
        if(Controller1.ButtonLeft.pressing() && lift.value(percentUnits::pct) < liftTowerLow)
        {
          liftTo(liftTowerLow, 12);
        }
        else if(Controller1.ButtonLeft.pressing() && std::abs(lift.value(percentUnits::pct) - liftTowerMid) <= 2)
        {
          liftTo(liftMin, 12);
        }
        else if(Controller1.ButtonLeft.pressing() && std::abs(lift.value(percentUnits::pct) - liftTowerLow) <= 2 && !(std::abs(lift.value(percentUnits::pct) - liftTowerMid) <= 2))
        {
          liftTo(liftTowerMid, 12);
        }

        /*
      // -----------------------------Flip Out
      if(Controller1.ButtonRight.pressing())
      {
        Brain.Timer.reset();
        flipOut();
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("%d ", Brain.Timer.time());  
      }*/

        //Press Y to run autonomus
        /*
        if(Controller1.ButtonY.pressing())
        {
          autonomous();
        }
        */
/*
        if(mode == 2 && Controller1.ButtonR1.pressing() && Controller1.ButtonL1.pressing())
        {
          autonomous();
        }
*/
        // -----------------------------Test Mode (gets drive data for pid control)
        if(Test.pressing() == 1)
        {
          /*
          drive(2);
          vex::task::sleep(1000);
          drive(-1);
          */
          //turnFor(-90);
        }
    }
}

#endif