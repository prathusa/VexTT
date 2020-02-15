#pragma once

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