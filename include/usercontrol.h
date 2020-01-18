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
        
        /*
        if(Controller1.ButtonB.pressing())
        {
            
            /*
            driveSpeedFactor = 1.5; //Makes robot slower
            Controller1.Screen.clearLine(1);
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Slow Mode");
            Controller1.rumble("-");
            */
        //}

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

        //Fade away
        if(Controller1.ButtonX.pressing()){
          //fadeAway();
          autonomous();
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
        // -----------------------------Toggle Lift Positions
        else if(Controller1.ButtonLeft.pressing())
        {
          liftTo(liftTower, 12);
          //turnTo(90, true, 10);
        }
        else if(Controller1.ButtonA.pressing())
        {
          liftTo(liftMin);
        }
        else 
        {
            Lift.setBrake(hold); //potentially make a custom hold function for the lift using potentiometer
            Lift.stop();
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
        // -----------------------------Debug Mode (gets drive data for pid control)
        if(Debug.pressing() == 1)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("Recording data");
          getData();
        }

        // -----------------------------Test Mode (gets drive data for pid control)
        if(Test.pressing() == 1)
        {
          Gyro.resetAngle();
          turnFor(47);
          vex::task::sleep(2000);
          sdt.turnToHeading(0, rotationUnits::deg, 40, velocityUnits::pct);
          vex::task::sleep(2000);
          sdt.turnFor(90, rotationUnits::deg, 40, velocityUnits::pct);
          vex::task::sleep(2000);
          sdt.turnToHeading(0, rotationUnits::deg, 40, velocityUnits::pct);
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