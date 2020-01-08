/*------------------------------------------------------------------------------------------------------
[MAIN] Sample Main Program > A sample main.cpp file for ACCESS_OS
------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++++
This is a sample main.cpp file for ACCESS_OS (Sample meaning not complete, a templete/base)

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
//Drive system class
#ifndef ROBOT_C
#define ROBOT_C
#include "robot-base.cpp"
#endif
//ACCESS_OS file
#ifndef ACCESS_OS_C
#define ACCESS_OS_C
#include "ACCESS_OS.cpp"
#endif

ROBOT_BASE ROBOT;
ACCESS_OS OS;

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Variables > Global variables for functions
------------------------------------------------------------------------------------------------------*/

//Movement const variables + calculations
const int circumference = (wheelDiameter * M_PI);	//M_PI is from the math library
const int oneTile = (360 * tileSize) / circumference;	//Calculate how many degrees it takes to move oneTile
const int rotateTile = oneTile / 2;	//If both motors spin at opposite directions at half of oneTile, it will turn 90 degrees

//For checking status
int tempStatus = 0;

/*------------------------------------------------------------------------------------------------------
[PROGRAM]

Functions are here. Read the comments to find out what each does.

------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[OPTIMIZING] autonRotateTile > Rotates left or right (Program for BLUE, it will auto-config for RED)
------------------------------------------------------------------------------------------------------*/
void autonRotateTile(float x, int speed, int delayTime) 
{
	//autonRotateTile v2019.5.14.17.20
	//Use x to rotate the robot by 90.
	//rotateTile needs to be calibrated and calculated to work correctly
	//Examples (for BLUE side): 
	//1. Rotate right 45 degrees:	autonRotateTile(x=.5, speed=100, delayTime=50);
	//2. Rotate right 90 degrees:	autonRotateTile(x=1, speed=100, delayTime=50);
	//3. Rotate left 180 degrees:	autonRotateTile(x=-2, speed=50, delayTime=50);

	ROBOT.timeOut(2.5);
	ROBOT.reset();

	if (OS.getValues(AUTON_COLOR) == RED) //If color is 1 (RED) flip the values 
	{
		x = -x;
	}
	x = x * rotateTile;

	LeftBaseM1.rotateTo(x, vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
	RightBaseM1.rotateTo(-x, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
}

/*------------------------------------------------------------------------------------------------------
[STABLE] driverScore > User scoring control systems
------------------------------------------------------------------------------------------------------*/
void driverScore()
{
	//Add scoring code here
}

/*------------------------------------------------------------------------------------------------------
[STABLE] pre_auton > Set up any initialization stuff here before auton
------------------------------------------------------------------------------------------------------*/
void pre_auton(void)
{
	ROBOT.reset();		//Resets the motor's position
	OS.menuCONFIG();	//Calls ACCESS_OS's menuCONFIG, the main reason why you downloaded this
	OS.notificationHUD("Robot: OK");	//Sends message to driver
}

/*------------------------------------------------------------------------------------------------------
[OPTIMIZING] autonFrontRow > A.I. scores in the front row
------------------------------------------------------------------------------------------------------*/
void autonFrontRow()
{
	//Add code for front row auton here
}

/*------------------------------------------------------------------------------------------------------
[OPTIMIZING] autonBackRow > Smooth moves by our A.I. back stage
------------------------------------------------------------------------------------------------------*/
void autonBackRow()
{
	//Add code for front row auton here
}

/*------------------------------------------------------------------------------------------------------
[OPTIMIZING] autonSkills > May you be charmed by the A.I.
------------------------------------------------------------------------------------------------------*/
void autonSkills()
{
	//Got Skills? Add code for skills here
}

/*------------------------------------------------------------------------------------------------------
[STABLE] autonomous > The heart and soul of our A.I.
------------------------------------------------------------------------------------------------------*/
void autonomous(void)
{
	//If configuration[1] is 0 (Front row), 1 (Back row), or 2 (Skills), run the correct auton
	if (OS.getValues(AUTON_TYPE) == FRONT) {
		autonFrontRow();
	}
	else if (OS.getValues(AUTON_TYPE) == BACK) {
		autonBackRow();
	}
	else if (OS.getValues(AUTON_TYPE) == SKILLS) {
		autonSkills();
	}

	//Auton end. Prints auton end on the controller + vibrate controller
	OS.notificationHUD("Auton: DONE");
	ROBOT.rumble();
}

/*------------------------------------------------------------------------------------------------------
[STABLE] usercontrol > Driver control stuff here, the A.I. is in your hands
------------------------------------------------------------------------------------------------------*/
void usercontrol(void)
{
	Brain.Screen.clearScreen(vex::color::green); //Get the driver control ready with visual cues
	//User control code here, inside the loop
	while (1) {
		switch (OS.getValues(AUTON_DRIVE))
		{
		case RC:
			ROBOT.RCDrive();
			break;
		case TANK:
			ROBOT.tankDrive();
			break;
		default:
			break;
		}
		driverScore();
	}
}

/*------------------------------------------------------------------------------------------------------
[STABLE] main > System required loop, (Can't?) add stuff here
------------------------------------------------------------------------------------------------------*/
int main()
{
	//Run the pre-autonomous function.
	pre_auton();

	//Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	//Prevent main from exiting with an infinite loop.
	while (1)
	{
		//Checks if current status changed. If it didn't, don't do anything. If it did, refresh statusHUD.
		if (tempStatus != OS.currStatus())
		{
			OS.statusHUD();
			tempStatus = OS.currStatus();
		}
		vex::task::sleep(175); //Sleep the task for a short amount of time to prevent wasted resources.
	}
}