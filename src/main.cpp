#include "main.h"
using namespace vex;
using namespace std;

int main() 
{
  // Run the pre-autonomous function.
  // Inertial.calibrate(2000);
  // vex::task::sleep(2000);
  pre_auton();
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1)
  {
    vex::task::sleep(20);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}
