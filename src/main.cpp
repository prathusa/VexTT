#include "main.h"
using namespace vex;
using namespace std;
// FPS fps = FPS();

void read()
{
  while(1)
  {
    std::cout << "Time: 10 ";
    std::cout << Brain.Timer.time(timeUnits::msec) << std::endl;
    std::cout << "Calc: 11 ";
    std::cout << robot.base.pid.output << std::endl;
    std::cout << "PIDPos: 12 ";
    std::cout << robot.base.pid.position << std::endl;
    std::cout << "DPos: 13 ";
    std::cout << d.position(rev) << std::endl;
    std::cout << "Velocity: 14 ";
    std::cout << d.velocity(percentUnits::pct) << std::endl;
    std::cout << "ImuPos: 15 ";
    std::cout << Inertial.rotation() << std::endl;
    std::cout << "Error: 16 ";
    std::cout << robot.base.pid.error << std::endl;
    std::cout << "Integral: 17 ";
    std::cout << robot.base.pid.integral << std::endl;
    std::cout << "Derivative: 18 ";
    std::cout << robot.base.pid.derivative << std::endl;
    std::cout << "Pout: 19 ";
    std::cout << robot.base.pid.Pout << std::endl;
    std::cout << "Iout: 20 ";
    std::cout << robot.base.pid.Iout << std::endl;
    std::cout << "Dout: 21 ";
    std::cout << robot.base.pid.Dout << std::endl;
    // std::cout << "Theta Volts: ";
    // std::cout << robot.base.thetaVolts * 4 << std::endl;
    
    cout << std::endl;
    this_thread::sleep_for(100);
  }
}

int main() 
{
  // // Run the pre-autonomous function.
  // Inertial.calibrate(2000);
  // vex::task::sleep(2000);
  // pre_auton();
  // Brain.Screen.clearScreen();
  // Brain.Screen.setFont(fontType::mono60);
  // Brain.Screen.setFillColor(RED);
  // cout << "3" << endl;
  // Brain.Screen.print("3");
  // Brain.Screen.clearScreen();
  // vex::task::sleep(100);
  // cout << "2" << endl;
  // Brain.Screen.print("2");
  // Brain.Screen.clearScreen();
  // vex::task::sleep(100);
  // cout << "1" << endl;
  // Brain.Screen.print("1");
  // vex::task::sleep(100);
  // Brain.Screen.clearScreen();
  // cout << "GO!" << endl;
  // Brain.Screen.print("GO!");
      // thread reader = thread(read);
      // fps.setUpdate(TWO_MOTOR_ENC);
      // fps.print();
      // usercontrol();
  // tune(.03);
//   robot.imu.setPrecise();
//   robot.imu.To(90);
  // robot.base.setIntake();

  // robot.imu.setPrecise();
  // robot.base.setPrecise();
  // Brain.Timer.reset();
  // robot.base.To(1, 90);
  // vex::task::sleep(500);
  // robot.base.To(0, 0);
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




  // robot.base.setPrecise();
  // robot.base.To(1, 0);
  // robot.map.frontTo(0, 2);
  // vex::task::sleep(1000);
  // robot.map.frontTo(0, 0);
  // vex::task::sleep(1000);
  // robot.map.frontTo(0, 1);





  // tune(0.05);





















  // Prevent main from exiting with an infinite loop.
  while (1)
  {
    vex::task::sleep(20);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}
