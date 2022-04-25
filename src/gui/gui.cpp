#include "main.h"

void battery_check()
{
  while(1)
  {
    if(Brain.Battery.capacity() > 60)
    {
      Brain.Screen.setFillColor(vex::green);
      Brain.Screen.setPenColor(vex::black);
    }
    else if(Brain.Battery.capacity() > 30)
    {
      Brain.Screen.setFillColor(vex::yellow);
      Brain.Screen.setPenColor(vex::black);
    }
    else
    {
      Brain.Screen.setFillColor(vex::red);
      Brain.Screen.setPenColor(vex::black);
    }
    Brain.Screen.printAt(0, 15, "Battery Percent%: %d", Brain.Battery.capacity());
    Brain.Screen.setFillColor(vex::black);
    Brain.Screen.setPenColor(vex::white);
    this_thread::sleep_for(100);
  }
}

void pre_auton(void) 
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Calibrating");
    // Gyro.calibrate(2000);
    Inertial.calibrate(2000);
    task::sleep(2000);
    // while(Inertial.isCalibrating())
    // {
    //   vex::task::sleep(20);
    // }
    ROBOT::motors = config::MOTORS::BASE;
    // robot.fps.setUpdate(config::SENSORS::TWO_MOTOR_ENC);
    ROBOT::sensors = config::SENSORS::TWO_MOTOR_ENC;
    robot.fps.start();
    Controller1.Screen.clearScreen();
    // Brain.Screen.drawImageFromFile("1.png", 0, 0);

    thread battery_update = thread(battery_check);
    battery_update.setPriority(1);

    os.menuCONFIG();	//Calls ACCESS_OS's menuCONFIG, the main reason why you downloaded this
}