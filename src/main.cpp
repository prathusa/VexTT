#include "vex.h"

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
    std::cout << LeftFrontMotor.position(rev) << std::endl;
    vex::task::sleep(200);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}