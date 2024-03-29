#include "main.h"
using namespace vex;
using namespace std;

// Most global initializations occur in config.cpp
int main() 
{
  // Run the pre-autonomous function.
  // Inertial.calibrate(2000);
  // vex::task::sleep(2000);
  pre_auton();

  // d.rotateFor(directionType::fwd, 1, rotationUnits::rev);

  // robot.to.update(feature::Coordinate(0, 1, 0, 0, feature::Coordinate::rotationType::DEG));
  // robot.to.wait();
  // robot.to.update(feature::Coordinate(0, -1, 0, 0, feature::Coordinate::rotationType::DEG));
  // robot.to.tuner(feature::Coordinate(0, 1, 0, 0, feature::Coordinate::rotationType::DEG));
  // // robot.to.update(feature::Coordinate(1, 1, 0, 45, feature::Coordinate::rotationType::DEG));
  dt.driveFor(fwd, 12, distanceUnits::in);
  while (robot.to.status == TO::STATUS::RUNNING)
  {
    cout << robot.to.pos << '\n';
    vex::task::sleep(100);
  }
  cout << "status : " << robot.to.status << endl;

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
