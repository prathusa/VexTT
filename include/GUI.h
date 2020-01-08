//GUI
#ifndef GUI_H
#define GUI_H

#include "vex.h"
#include "record.h"
#include "controls.h"
#include "manual.h"
#include "autonomous.h"

bool rec;
void pre_auton(void) 
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Calibrating Sensors...");
    Inertial.calibrate(2000);
    while(Inertial.isCalibrating())
    {
      vex::task::sleep(20);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Calibration Complete!");

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

	  OS.menuCONFIG();	//Calls ACCESS_OS's menuCONFIG, the main reason why you downloaded this
	  OS.notificationHUD("Robot: OK");	//Sends message to driver
}


#endif