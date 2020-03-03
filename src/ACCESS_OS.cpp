#include "vex.h"

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
// int ACCESS_OS::currStatus()
// {
// 	int status;
// 	if (Competition.isEnabled()) //If robot is enabled, check what mode/period the match is in
// 	{
// 		if (Competition.isAutonomous()) {
// 			status = modeAuton; //Robot is in Autonomous mode
// 		}
// 		else if (Competition.isDriverControl()) {
// 			status = modeDriver; //Robot is in Driver Control mode
// 		}
// 		else
// 		{
// 			status = modeError; //ERROR MODE
// 		}
// 	}
// 	else
// 	{
// 		status = modeDisabled; //Robot is Disabled
// 	}
// 	return status;
// }

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
void ACCESS_OS::menuCONFIG() 
{
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
