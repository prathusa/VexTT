#include "GUI.h"
#include "autonomous.h"
#include "drivefunctions.h"
#include "usercontrol.h"


int main() 
{
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1) 
  {
    // Checks if current status changed. If it didn't, don't do anything. If it
    // did, refresh statusHUD.
    if (tempStatus != OS.currStatus()) 
    {
      OS.statusHUD();
      tempStatus = OS.currStatus();
    }
    vex::task::sleep(20);
    // vex::task::sleep(175); //Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}