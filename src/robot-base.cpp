#include "vex.h"

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
	Controller1.rumble(".");
}

/*------------------------------------------------------------------------------------------------------
[STABLE] driveStop > Stops drive motors
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::stop(bool coastOrBrake)
{
	if (coastOrBrake == true)
	{
		l.stop(vex::brakeType::brake);
		r.stop(vex::brakeType::brake);
	}
	else
	{
		l.stop(vex::brakeType::coast);
		r.stop(vex::brakeType::coast);
	}
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] tankDrive > Tank drive control system
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::tankDrive()
{
	
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
	l.setTimeout(timeout, vex::timeUnits::sec);
	r.setTimeout(timeout, vex::timeUnits::sec);
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] resetDrive > Resets rotation count of drive motors
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::resetDrive()
{
	l.setRotation(0, vex::rotationUnits::deg);
	r.setRotation(0, vex::rotationUnits::deg);
}

/*------------------------------------------------------------------------------------------------------
[STABLE - USER] reset > Combination of all the reset functions
------------------------------------------------------------------------------------------------------*/
void ROBOT_BASE::reset()
{
	resetDrive();
}
