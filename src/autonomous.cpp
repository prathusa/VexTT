#include "vex.h"

void autonomous(void) 
{
    //If configuration[1] is 0 (Front row), 1 (Back row), or 2 (Skills), run the correct auton
	if(!robot.allInstalled())
  {
    if(robot.driveInstalled())
    {
      if(os.getValues(POSITION) == FRONT)
      {

      }
    }
  }
  else if(os.getValues(POSITION) == BRAIN)
    goto Brain;
  else if (os.getValues(POSITION) == FRONT) 
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
      //p7();
      p6();
    }
    else if(os.getValues(POINTS) == EIGHT)
    {
      //p8();
      p6();
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
      u5();
    }
    else if(os.getValues(POINTS) == FOUR)
    {
      u5();
      //u4(); non existant rn
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

  Brain:
  if (manual && rojo)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("RM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        u5();
    }
    else if (manual && azul)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("BM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        u5();
    }
    else if (( rojo || azul || skills || slow || test))
    {
      int row = 1;
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(fontType::mono60);
      Brain.Screen.setCursor(0, row);

      if(rojo)
      {
        Controller1.Screen.print("RED");
        Brain.Screen.setFillColor(red);
        Brain.Screen.print("RED");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(azul)
      {
        Controller1.Screen.print("BLUE");
        Brain.Screen.setFillColor(blue);
        Brain.Screen.print("BLUE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(skills)
      {
        Controller1.Screen.print(" SK");
        Brain.Screen.setFillColor(yellow);
        Brain.Screen.print("SKILLS");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(slow)
      {
        Controller1.Screen.print(" SLOW");
        Brain.Screen.setFillColor(orange);
        Brain.Screen.print("SLOW MODE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      if(test)
      {
        Controller1.Screen.print(" TEST");
        Brain.Screen.setFillColor(purple);
        Brain.Screen.print("TEST MODE");
        row += 1;
        Brain.Screen.setCursor(row, 0);
      }

      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("By: Pratham");
      if(!skills)
      {
        //play();
      }
      else 
      {
        //splay();
      }
    }
    else 
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(":( i sleep");
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("By: Pratham");
    }

	//Auton end. Prints auton end on the controller + vibrate controller
	os.notificationHUD("Auton: DONE");
}
