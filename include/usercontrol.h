#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "vex.h"
#include "controls.h"
#include "autonomous.h"
#include "drivefunctions.h"

void usercontrol(void) 
{
    //tiltTo(tiltMin, 2.5);
    while(1) 
    {
        controls();
        
        //Press Y to run autonomus
        /*
        if(Controller1.ButtonY.pressing())
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