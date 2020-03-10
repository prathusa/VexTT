#include "vex.h"

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
    Brain.Screen.print("Battery Percent%: %d", Brain.Battery.capacity());
    Brain.Screen.setFillColor(vex::black);
    Brain.Screen.setPenColor(vex::white);
    this_thread::sleep_for(10000);
  }
}

void pre_auton(void) 
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Calibrating");
    // Gyro.calibrate(2000);
    Inertial.calibrate(2000);
    while(Inertial.isCalibrating())
    {
      vex::task::sleep(20);
    }
    Controller1.Screen.clearScreen();
    Brain.Screen.drawImageFromFile("1.png", 0, 0);

    thread battery_update = thread(battery_check);
    battery_update.setPriority(1);

    os.menuCONFIG();	//Calls ACCESS_OS's menuCONFIG, the main reason why you downloaded this
}