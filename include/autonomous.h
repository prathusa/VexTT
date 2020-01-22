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
	if (OS.getValues(AUTON_POS) == FRONT) 
  {
    if(OS.getValues(AUTON_PNTS) == FOUR)
    {
      p4();
    }
    else if(OS.getValues(AUTON_PNTS) == FIVE)
    {
      p5();
    }
    else if(OS.getValues(AUTON_PNTS) == SIX)
    {
      p6();
    }
	}
	else if (OS.getValues(AUTON_POS) == BACK) 
  {
		
    if(OS.getValues(AUTON_PNTS) == FOUR)
    {
      u5();
      //u4(); non existant rn
    }
    else if(OS.getValues(AUTON_PNTS) == FIVE)
    {
      u5();
    }
    else if(OS.getValues(AUTON_PNTS) == SIX)
    {
      u6();
    }
    //to be made
    /*else if(OS.getValues(AUTON_PNTS) == SEVEN)
    {
      u7();
    }*/
    else if(OS.getValues(AUTON_PNTS) == EIGHT)
    {
      u8();
    }
	}
	else if (OS.getValues(AUTON_POS) == SKILLS) 
  {
		autonSkills();
	}
  else if (OS.getValues(AUTON_POS) == AMBI) 
  {
		autonAmbi();
	}

	//Auton end. Prints auton end on the controller + vibrate controller
	OS.notificationHUD("Auton: DONE");
	ROBOT.rumble();
}
#endif /* AUTONOMUS_H */