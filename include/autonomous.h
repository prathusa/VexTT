#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "record.h"
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
#include "vex.h"

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
#endif /* AUTONOMUS_H */