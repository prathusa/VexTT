/*------------------------------------------------------------------------------------------------------
[CLASS] robot-base > Drive control systems and replacement system functions
Main program MUST have these lines of code on top:
//Drive system class
#ifndef ROBOT_C
#define ROBOT_C
#include "robot-base.cpp"
#endif
------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++++
This is a sample robot-base.cpp file for ACCESS_OS (Sample meaning not complete, a templete/base)

The robot specs are as follows:
2 motor omniwheel drive

A small batch of example programs are provided, but you'll need to modify the code to fit your robot.

Changelog, documentation, and more information can be found at the ACCESS_OS website.
Link to website: https://dev.azure.com/roboVEX/_git/ACCESS_OS
------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Includes > Include needed external libraries and files
------------------------------------------------------------------------------------------------------*/
//Connected devices file
#ifndef CONFIG_H
#define CONFIG_H
#include "robot-config.h"
#endif

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Defines > Constant vars that won't change during program run
------------------------------------------------------------------------------------------------------*/
//Sizes for movement defined
#define wheelDiameter			4		//wheelDiameter is the diameter of our wheels in inches
#define tileSize				23.5	//Each tile is ~23.5 inches across from one side to another
#define centerTile				.5		//Approx. move from edge to center of tile

//Joystick jitter fix defined
#define deadSpace				5		//Stop controller jitter!

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Defines > Constant vars that won't change during program run
------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[CLASS] ROBOT_BASE > Drive control systems and replacement system functions
------------------------------------------------------------------------------------------------------*/
class ROBOT_BASE {

private:
	/*------------------------------------------------------------------------------------------------------
	[PRIVATE] Variables > Private variables for drive functions
	------------------------------------------------------------------------------------------------------*/
	//const int deadThreshold = -15; //Replaced with deadSpace, which is above

public:
	/*------------------------------------------------------------------------------------------------------
	[PUBLIC] Functions > Public functions for people to use
	------------------------------------------------------------------------------------------------------*/
	//Do we need this?
	ROBOT_BASE();

	//System functions
	void delay(int d);
	void rumble();

	//Drive functions
	void stop(bool coastOrBrake);
	void tankDrive();
	void RCDrive();
	void MECDrive();
	void timeOut(float timeout);
	void resetDrive();
	void reset();
};

/*------------------------------------------------------------------------------------------------------
[STABLE] ROBOT_BASE > Initialization
------------------------------------------------------------------------------------------------------*/
ROBOT_BASE::ROBOT_BASE() {}

/*------------------------------------------------------------------------------------------------------
[STABLE - SYSTEM] delay > Use as replacement for the system's vex::task::sleep
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::delay(int d)
{
	vex::task::sleep(d);
}

/*------------------------------------------------------------------------------------------------------
[STABLE - SYSTEM] rumble > User feedback through controller's rumble motors
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::rumble()
{
	Controller.rumble(".");
}

/*------------------------------------------------------------------------------------------------------
[STABLE] driveStop > Stops drive motors
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::stop(bool coastOrBrake)
{
	if (coastOrBrake == true)
	{
		LeftBaseM1.stop(vex::brakeType::brake);
		RightBaseM1.stop(vex::brakeType::brake);
	}
	else
	{
		LeftBaseM1.stop(vex::brakeType::coast);
		RightBaseM1.stop(vex::brakeType::coast);
	}
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] tankDrive > Tank drive control system
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::tankDrive()
{	
	//Add drive system code here
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] RCDrive > RC-style drive control system
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::RCDrive()
{
	//Add drive system code here
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] driveTimeOut > how many seconds before motors are disabled due to error
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::timeOut(float timeout)
{
	LeftBaseM1.setTimeout(timeout, vex::timeUnits::sec);
	RightBaseM1.setTimeout(timeout, vex::timeUnits::sec);
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] resetDrive > Resets rotation count of drive motors
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::resetDrive()
{
	LeftBaseM1.setRotation(0, vex::rotationUnits::deg);
	RightBaseM1.setRotation(0, vex::rotationUnits::deg);
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] reset > Combination of all the reset functions
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::reset()
{
	resetDrive();
}