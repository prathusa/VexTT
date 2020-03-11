#include "vex.h"
using namespace vex;
using namespace std;

void read()
{
  while(1)
  {
    std::cout << "Calc: ";
    std::cout << robot.imu.pid.output << std::endl;
    std::cout << "Position: ";
    std::cout << robot.imu.pid.position << std::endl;
    std::cout << "Drive Position: ";
    std::cout << d.position(rev) << std::endl;
    std::cout << "Inertial Position: ";
    std::cout << Inertial.rotation() << std::endl;
    std::cout << "Error: ";
    std::cout << robot.imu.pid.error << std::endl;
    std::cout << "Integral: ";
    std::cout << robot.imu.pid.integral << std::endl;
    std::cout << "Derivative: ";
    std::cout << robot.imu.pid.derivative << std::endl;
    std::cout << "Pout: ";
    std::cout << robot.imu.pid.Pout << std::endl;
    std::cout << "Iout: ";
    std::cout << robot.imu.pid.Iout << std::endl;
    std::cout << "Dout: ";
    std::cout << robot.imu.pid.Dout << std::endl;
    std::cout << "Velocity: ";
    std::cout << d.velocity(percentUnits::pct) << std::endl;
    cout << std::endl;
    this_thread::sleep_for(20);
  }
}

int main() 
{
  // // Run the pre-autonomous function.
  thread reader = thread(read);
  Inertial.calibrate(2000);
  vex::task::sleep(2000);
  robot.imu.setPrecise();
  robot.imu.To(90);
  // robot.base.setIntake();
  // robot.base.To(1);
  // d.spin(fwd, 1, pct);
  // pre_auton();
  // // thread a = thread(read);
  // // usercontrol();
  // // Inertial.calibrate(2000);
  // // vex::task::sleep(2000);
  
  // // // Set up callbacks for autonomous and driver control periods.
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