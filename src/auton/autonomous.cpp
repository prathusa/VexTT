#include "main.h"

void autonomous(void) 
{
    //If configuration[1] is 0 (Front row), 1 (Back row), or 2 (Skills), run the correct auton
  if (os.getValues(POSITION) == FRONT) 
  {
    if(os.getValues(POINTS) == ONE)
    {
      autonAmbi();
    }
    else if(os.getValues(POINTS) == THREE)
    {
      p3();
    }
    else if(os.getValues(POINTS) == FOUR)
    {
      p4();
    }
    else if(os.getValues(POINTS) == FIVE)
    {
      p5();
    }
    else if(os.getValues(POINTS) == SIX)
    {
      p6();
    }
    else if(os.getValues(POINTS) == SEVEN)
    {
      p7();
    }
    else if(os.getValues(POINTS) == EIGHT)
    {
      p8();
    }
	}
	else if (os.getValues(POSITION) == BACK) 
  {
		if(os.getValues(POINTS) == ONE)
    {
      autonAmbi();
    }
    else if(os.getValues(POINTS) == THREE)
    {
      u3();
    }
    else if(os.getValues(POINTS) == FOUR)
    {
      u4();
    }
    else if(os.getValues(POINTS) == FIVE)
    {
      u5();
    }
    else if(os.getValues(POINTS) == SIX)
    {
      u6();
    }
    //to be made
    else if(os.getValues(POINTS) == SEVEN)
    {
      u7();
    }
    else if(os.getValues(POINTS) == EIGHT)
    {
      tu7();
    }
	}
	else if (os.getValues(POSITION) == SKILLS) 
  {
		if(os.getValues(POINTS) == EIGHTTEEN)
    {
      s18();
    }
    else if(os.getValues(POINTS) == FOURTY)
    {
      s40();
    }
	}
}
