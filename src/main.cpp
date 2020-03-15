#include "vex.h"
using namespace vex;
using namespace std;

void read()
{
  while(1)
  {
    std::cout << "Calc: ";
    std::cout << robot.base.pid.output << std::endl;
    std::cout << "PID Pos: ";
    std::cout << robot.base.pid.position << std::endl;
    std::cout << "D Pos: ";
    std::cout << d.position(rev) << std::endl;
    std::cout << "Inertial Pos: ";
    std::cout << Inertial.rotation() << std::endl;
    std::cout << "Error: ";
    std::cout << robot.base.pid.error << std::endl;
    std::cout << "Integral: ";
    std::cout << robot.base.pid.integral << std::endl;
    std::cout << "Derivative: ";
    std::cout << robot.base.pid.derivative << std::endl;
    std::cout << "Pout: ";
    std::cout << robot.base.pid.Pout << std::endl;
    std::cout << "Iout: ";
    std::cout << robot.base.pid.Iout << std::endl;
    std::cout << "Dout: ";
    std::cout << robot.base.pid.Dout << std::endl;
    // std::cout << "Theta Volts: ";
    // std::cout << robot.base.thetaVolts * 4 << std::endl;
    std::cout << "Velocity: ";
    std::cout << d.velocity(percentUnits::pct) << std::endl;
    cout << std::endl;
    this_thread::sleep_for(30);
  }
}

int main() 
{
  // // Run the pre-autonomous function.
  Inertial.calibrate(2000);
  vex::task::sleep(2000);
  
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(fontType::mono60);
  Brain.Screen.setFillColor(RED);
  cout << "3" << endl;
  Brain.Screen.print("3");
  Brain.Screen.clearScreen();
  vex::task::sleep(100);
  cout << "2" << endl;
  Brain.Screen.print("2");
  Brain.Screen.clearScreen();
  vex::task::sleep(100);
  cout << "1" << endl;
  Brain.Screen.print("1");
  vex::task::sleep(100);
  Brain.Screen.clearScreen();
  cout << "GO!" << endl;
  Brain.Screen.print("GO!");
  thread reader = thread(read);
  
//   robot.imu.setPrecise();
//   robot.imu.To(90);
  // robot.base.setIntake();

  // robot.imu.setPrecise();
  robot.base.setPrecise();
  robot.base.For(1, 0);
  // robot.imu.To(90);
  // robot.base.For(1, -90);
  // robot.imu.To(270);
  // robot.base.For(-1);
  // robot.imu.To(180);
  // d.spin(fwd, 20, pct);
  // pre_auton();
  // // thread a = thread(read);
  // usercontrol();
  
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
