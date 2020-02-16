#include "vex.h"

int main() 
{
  
  // Run the pre-autonomous function.
  // pre_auton();
  RightFrontMotor.spin(forward);
  std::cout << RightFrontMotor.position(rev) << std::endl;
  //LeftFrontMotor.spin(forward);
  // robot.turn(90);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1) 
  {
    std::cout << LeftFrontMotor.position(rev) << std::endl;
    vex::task::sleep(200);
    // vex::task::sleep(175); //Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}