#include "main.h"
using namespace vex;
using namespace std;

void read()
{
  while(1)
  {
    std::cout << "Calc: ";
    std::cout << robot.pid.calc_pid() << std::endl;
    std::cout << "Position: ";
    std::cout << d.position(rev) << std::endl;
    // std::cout << "Target: ";
    // std::cout << robot.pid.target << std::endl;
    // std::cout << "Error: ";
    // std::cout << robot.pid.error << std::endl;
    task::sleep(100);
  }
}

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
    vex::task::sleep(20);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}