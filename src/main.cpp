#include "vex.h"
using namespace vex;
using namespace std;

void readTest(void *arg)
{
  while(1)
  {
    cout << (*(pot *) arg).value(pct) << endl;
    this_thread::sleep_for(100);
  }
}

void read()
{
  while(1)
  {
    std::cout << "Calc: ";
    std::cout << "f" << std::endl;
    std::cout << "Position: ";
    std::cout << "p" << std::endl;
    std::cout << "Error: ";
    std::cout << "e" << std::endl;
    std::cout << "Integral: ";
    std::cout << "i" << std::endl;
    std::cout << "Derivative: ";
    std::cout << "d" << std::endl;
    cout << std::endl;
    // std::cout << "Target: ";
    // std::cout << robot.pid.target << std::endl;
    // std::cout << "Error: ";
    // std::cout << robot.pid.error << std::endl;
    this_thread::sleep_for(100);
  }
}

int main() 
{
  // // Run the pre-autonomous function.
  // pre_auton();
  // robot.lifter.pid.setPotDRLift();
  // robot.lifter.pid.setTarget(62);
  // robot.lifter.pid.setPotDR();
  // robot.lifter.pid.async(57);
  // thread a = thread(read);
  // thread a = thread(read);
  robot.tilter.setTilt();
  robot.tilter.To(60);
  // Inertial.calibrate(1000);
  // vex::task::sleep(1000);
  // robot.imu.turn(45, 0);
  // sdt.turnFor(90, rotationUnits::deg);

  // //robot.lifter.pid.setPID(3, 0.3, .05);
  // robot.lifter.pid.setEncDRLift();
  // robot.lifter.pid.async(.7);

  // void *ptr;
  // ptr = &lift;
  // thread pointer_thread = thread(readTest, ptr);
  
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