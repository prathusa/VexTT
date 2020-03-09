#include "vex.h"
using namespace vex;
using namespace std;

void read()
{
  while(1)
  {
    std::cout << "Calc: ";
    std::cout << robot.base.output << std::endl;
    std::cout << "Position: ";
    std::cout << robot.base.position << std::endl;
    std::cout << "Inertial Position: ";
    std::cout << Inertial.rotation() << std::endl;
    std::cout << "Error: ";
    std::cout << robot.base.Pout << std::endl;
    std::cout << "Integral: ";
    std::cout << robot.base.Iout << std::endl;
    std::cout << "Derivative: ";
    std::cout << robot.base.Dout << std::endl;
    std::cout << "Velocity: ";
    std::cout << d.velocity(percentUnits::pct) << std::endl;
    cout << std::endl;
    this_thread::sleep_for(20);
  }
}

int main() 
{
  // // Run the pre-autonomous function.
  // pre_auton();
  thread a = thread(read);
  // robot.base.setBase();
  // robot.base.For(-1.5);
  // vex::task::sleep(100);
  robot.imu.setIMU();
  robot.imu.To(90);
  // robot.base.setBase();
  // robot.base.For(3.5);
  // // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  // Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1)
  {
    vex::task::sleep(20);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}