/*------------------------------------------------------------------------------------------------------
[CLASS] ACCESS_OS > Autonomous Control Center Selection System
Main file need these lines of code on top:
//ACCESS_OS file
#ifndef ACCESS_OS_C
#define ACCESS_OS_C
#include "ACCESS_OS.cpp"
#endif
------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++++
Welcome to the ACCESS_OS class. Here, you can configure settings, display text, and check robot status.

A small batch of example programs are provided, but you'll need to modify the code to fit your robot.

Changelog, documentation, and more information can be found at the ACCESS_OS website.
Link to website: https://dev.azure.com/roboVEX/_git/ACCESS_OS
------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Includes > Include needed external libraries and files
------------------------------------------------------------------------------------------------------*/
//Connected devices file
#ifndef VEX2_H
#define VEX2_H
#include "vex.h"
#endif

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Variables for ACCESS_OS > Constant vars that won't change during program run
------------------------------------------------------------------------------------------------------*/
//Define buttons for easy coding
#define btnNONE			0
#define btnUP				1
#define btnDOWN			2
#define btnLEFT			3
#define btnRIGHT		4
#define btnA				5
#define btnB				6
#define btnX				7
#define btnY				8
#define btnR1				9
#define btnR2				10
#define btnL1				11
#define btnL2				12

//Define delays
#define bounceDelay			20		//Time to wait between reads to check for key bounce
#define refreshDelay		150		//Time to wait between refreshing screens

//Define usable screen space for easy coding
#define screenTextWidth		16		//Max characters you can print on one line
#define screenTextHeight	3		//Max lines of text that can show on the controller

//Define max entries in 2d array for easy coding
#define maxMenus			3		//Make this the same # as items in maxMenusIndex
#define maxOptions			4		//Make this the same # as items in 2D of menuDisplayIndex

//Define robot status for easy coding
#define modeDisabled		0
#define modeDriver			1
#define modeAuton			2
#define modeError			3

//Define more robot info for easy coding
#define BLUE						0
#define RED							1
#define FRONT						0
#define BACK						1
#define SKILLS		  				2
#define ONE							0
#define THREE						1
#define FOUR						2
#define FIVE						3
#define SIX							4
#define EIGHT						5
#define AUTON_COLOR			0
#define AUTON_POS				1
#define AUTON_PNTS			2


/*------------------------------------------------------------------------------------------------------
[CLASS] ACCESS_OS > Defines class functions
------------------------------------------------------------------------------------------------------*/
class ACCESS_OS {
private:
	int keyPressedRaw();		//Raw button inputs
	bool isCursorOn = false;	//Flag for if cursor is showing or not

	/*------------------------------------------------------------------------------------------------------
	[GLOBAL] Arrays for ACCESS_OS > ACCESS_OS needed stuff
	------------------------------------------------------------------------------------------------------*/
	//1D array for displaying robot status
	std::string robotStatus[4] =
	{
		"!Robot Disabled!",
		"Driver Control",
		"Auton Control",
		"!! MODE ERROR !!"
	};

	//1D Array for max options in menu
	int maxMenusIndex[maxMenus] =
	{
		3,
		4,
		5
	};

	//1D Array for default selected options.
	//NOTE: Changing the values here will change the default options
	int configuration[maxMenus] =
	{
		0,
		0,
		3
	};

	//1D array for displaying the menu types
	std::string menuTypes[maxMenus] =
	{
		"Color: ",
		"Pos: ",
		"Pnts: "
	};

	//2D array for displaying the menu options
	std::string menuOptions[maxMenus][maxOptions] =
	{
		{ "Blue",	"Red",		"" }, //If "" doesn't work, try "NULL"
		{ "Front",	"Back",		"Skills",		"Ambi" },
		{ "4",		"5",		"6", 		"8" }
	};
public:
	ACCESS_OS();											//???
	int keyPressed();										//Filtered button inputs
	int currStatus();										//Gets current robot status
	void clearLine(int l_row);								//Smart row clearer
	void clearScreen();										//Smart screen clearer
	void print(std::string text, int row, int col);			//Prints without overwriting selector
	void selector(int row);									//Prints selector
	void displayMenu(int currRow, int configuration[]);		//Prints config menu
	int getValues(int wantConfig);							//Returns current values of configuration[]

	//Pre-built programs
	void notificationHUD(std::string str);					//Prints a message on first line
	void statusHUD();										//Prints current robot status on two lines
	void menuCONFIG();										//Runs complete config menu
};

/*------------------------------------------------------------------------------------------------------
[UNKNOWN] ACCESS_OS > ???
------------------------------------------------------------------------------------------------------*/
ACCESS_OS::ACCESS_OS() {}

/*------------------------------------------------------------------------------------------------------
[STABLE] keyPressedRaw > Returns raw values for button pressed
------------------------------------------------------------------------------------------------------*/
int ACCESS_OS::keyPressedRaw()
{
	if (Controller1.ButtonUp.pressing() == true)
	{
		return btnUP;
	}
	if (Controller1.ButtonDown.pressing() == true)
	{
		return btnDOWN;
	}
	if (Controller1.ButtonLeft.pressing() == true)
	{
		return btnLEFT;
	}
	if (Controller1.ButtonRight.pressing() == true)
	{
		return btnRIGHT;
	}
	if (Controller1.ButtonA.pressing() == true)
	{
		return btnA;
	}
	if (Controller1.ButtonB.pressing() == true)
	{
		return btnB;
	}
	if (Controller1.ButtonX.pressing() == true)
	{
		return btnX;
	}
	if (Controller1.ButtonY.pressing() == true)
	{
		return btnY;
	}
	if (Controller1.ButtonR1.pressing() == true)
	{
		return btnR1;
	}
	if (Controller1.ButtonR2.pressing() == true)
	{
		return btnR2;
	}
	if (Controller1.ButtonL1.pressing() == true)
	{
		return btnL1;
	}
	if (Controller1.ButtonL2.pressing() == true)
	{
		return btnL2;
	}
	else
	{
		return btnNONE;
	}
}

/*------------------------------------------------------------------------------------------------------
[STABLE] keyPressed > Returns clean values (no bounce) for button pressed
------------------------------------------------------------------------------------------------------*/
int ACCESS_OS::keyPressed()
{
	int noBounceKey = keyPressedRaw();
	vex::task::sleep(bounceDelay);
	if (noBounceKey == keyPressedRaw())
	{
		return noBounceKey;
	}
	else
	{
		return btnNONE;
	}
}

/*------------------------------------------------------------------------------------------------------
[TO BE UPGRADED] currStatus > Returns 0 (Disabled), 1 (Auton), or 2 (Driver)
------------------------------------------------------------------------------------------------------*/
int ACCESS_OS::currStatus()
{
	int status;
	if (Competition.isEnabled()) //If robot is enabled, check what mode/period the match is in
	{
		if (Competition.isAutonomous()) {
			status = modeAuton; //Robot is in Autonomous mode
		}
		else if (Competition.isDriverControl()) {
			status = modeDriver; //Robot is in Driver Control mode
		}
		else
		{
			status = modeError; //ERROR MODE
		}
	}
	else
	{
		status = modeDisabled; //Robot is Disabled
	}
	return status;
}

/*------------------------------------------------------------------------------------------------------
[UPGRADED] clearLine > ACCESS_OS replacement for the controller's Screen.clearLine
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::clearLine(int l_row) //select what row to clear but not selector if isCursorOn = true
{
	if (isCursorOn == true)
	{
		Controller1.Screen.setCursor(l_row + 1, 2);	//Prevent overwrite of selector GUI
		Controller1.Screen.print("               "); //15 spaces (1 less than screenTextWidth)
	}
	else
	{
		Controller1.Screen.clearLine();	//If isCursorOn = false, wipe line with system clearLine
	}
}

/*------------------------------------------------------------------------------------------------------
[UPGRADED] clearScreen > ACCESS_OS replacement for the controller's Screen.clearScreen
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::clearScreen() //clears everything but not selector if isCursorOn = true
{
	if (isCursorOn == true)
	{
		for (int row = 0; row < screenTextHeight; row++) //loops rows
		{
			clearLine(row);
		}
	}
	else
	{
		Controller1.Screen.clearScreen();	//If isCursorOn = false, wipe line with system clearScreen
	}

}

/*------------------------------------------------------------------------------------------------------
[UPGRADED] print > ACCESS_OS replacement for the controller's Screen.print
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::print(std::string text, int row, int col) //pass text, row, and col
{
	//NOTE: Does not call clearScreen, only clears current line
	clearLine(row);
	if (isCursorOn == true)
	{
		Controller1.Screen.setCursor(row + 1, col + 2); //Col + 2: Prevent overwrite of selector GUI
	}
	else
	{
		Controller1.Screen.setCursor(row + 1, col + 1); //Col + 1: Start from beginning
	}
	Controller1.Screen.print(text.c_str()); //Future GUI will scroll text
}

/*------------------------------------------------------------------------------------------------------
[UPGRADED] selector > pass 0, 1, or 2 to pick lines. (if more than 2, it jumps back to 0)
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::selector(int row) //pass which row you want the selector to be
{
	isCursorOn = true;
	for (int i = 1; i <= screenTextHeight; i++) //clears just the selector GUI
	{
		Controller1.Screen.setCursor(i, 1);
		Controller1.Screen.print("|");
	}

	//reminder of row == row mod / 3
	int showCursor = (row % screenTextHeight) + 1;
	Controller1.Screen.setCursor(showCursor, 1);
	Controller1.Screen.print(">");
}

/*------------------------------------------------------------------------------------------------------
[TO BE UPGRADED] displayMenu > Displays the actual menu (only works up to three menus)
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::displayMenu(int currRow, int configuration[]) //pass wanted selector row
{
	std::string temp;
	selector(currRow); //Display selector
	for (int i = 0; i < screenTextHeight; i++)
	{
		temp = menuTypes[i] + menuOptions[i][configuration[i]];
		print(temp, i, 0); //Display menu line i
	}
}

/*------------------------------------------------------------------------------------------------------
[STABLE] getValues > Returns asked value from configuration[] as int
------------------------------------------------------------------------------------------------------*/
int ACCESS_OS::getValues(int wantConfig)
{
	if (wantConfig > maxMenus)
	{
		return NULL;
	}
	else
	{
		return configuration[wantConfig];
	}
}


/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++++
Pre-built programs

Here is a small batch of programs that make use of ACCESS_OS's features.

- notificationHUD						Notification display. For use with status()
- statusHUD								Heads Up Display (HUD) of current robot status
- menuCONFIG							Complete config menu

Feel free to create your own programs and post them on the ACCESS_OS repo!

------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------
[STABLE] notificationHUD > Pre-built notification display. For use with status
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::notificationHUD(std::string str)
{
	//notificationHUD v2019.5.14.16.10
	//Displays text on line 1 to notify drivers.
	//Does not disappear unless overwritten.

	//Clears top row and prints user string
	clearLine(0);
	print(str, 0, 0);
}

/*------------------------------------------------------------------------------------------------------
[STABLE] statusHUD > Pre-built Heads Up Display (HUD) of current robot status
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::statusHUD() //v2 needs no overloading values
{
	//statusHUD v2019.5.14.16.10
	//Displays current robot status and selected options on row 2 and 3 respectively.
	//Needs to be in loop or else it won't refresh (future versions should self-refresh)

	std::string temp;
	//Display current robot status
	print(robotStatus[currStatus()], 1, 0); //Show current robot status on line 2
	//Display previously selected options
	temp = menuOptions[0][configuration[0]] + " " + menuOptions[1][configuration[1]] + " " + menuOptions[2][configuration[2]]; //Color + space + Row + space + Drive
	print(temp, 2, 0); //Show Color + Row on line 3
}

/*------------------------------------------------------------------------------------------------------
[STABLE] menuCONFIG > Pre-built complete config menu
------------------------------------------------------------------------------------------------------*/
void ACCESS_OS::menuCONFIG() {
	//menuCONFIG v2019.3.14.15.20
	//Use D-pad to move the cursor around the menu to select settings.
	//It automatically saves the settings as you change between options (left/right buttons).
	//Press A button to exit menu.
	//Planned upgrades are seperate threads to manage display and button presses

	isCursorOn = true;
	int currCursorMenu = 0;		//Goes up and down of array
	int currCursorOptions = 0;	//Goes left and right of array

	bool isAutonSelectScreen = true;
	while (isAutonSelectScreen == true)
	{
		displayMenu(currCursorMenu, configuration);	//Refreshes the screen with all the elements

		bool isValidButton = false;
		while (isValidButton == false) //Only updates screen if button was pressed
		{
			switch (keyPressed())
			{
			case(btnUP):				//If up button pressed
				isValidButton = true;
				currCursorMenu--;		//Go up the array

				//Get new values from configuration
				currCursorMenu = (currCursorMenu + maxMenus) % maxMenus; //currCursorMenu % the amount of items in 1D array
				currCursorOptions = configuration[currCursorMenu];
				break;
			case(btnDOWN):				//If down button pressed
				isValidButton = true;
				currCursorMenu++;		//Go down the array

				//Get new values from configuration
				currCursorMenu = (currCursorMenu + maxMenus) % maxMenus; //currCursorMenu % the amount of items in 1D array
				currCursorOptions = configuration[currCursorMenu];
				break;
			case(btnLEFT):				//If left button pressed
				isValidButton = true;
				currCursorOptions--;	//Shift left of array

				//Update values back into configuration
				currCursorOptions = (currCursorOptions + maxMenusIndex[currCursorMenu]) % maxMenusIndex[currCursorMenu]; //currCursorOptions % the amount of options in 1D array
				configuration[currCursorMenu] = currCursorOptions; //Assign current menu(row) option(col) to configuration array
				break;
			case(btnRIGHT):				//If right button pressed
				isValidButton = true;
				currCursorOptions++;	//Shift right of array

				//Update values back into configuration
				currCursorOptions = (currCursorOptions + maxMenusIndex[currCursorMenu]) % maxMenusIndex[currCursorMenu]; //currCursorOptions % the amount of options in 1D array
				configuration[currCursorMenu] = currCursorOptions; //Assign current menu(row) option(col) to configuration array
				break;
			case(btnA):					//Select auton and exit
				isValidButton = true;
				isAutonSelectScreen = false;
				isCursorOn = false;
				break;
			default:
				break;
			}
		}
	}
}
