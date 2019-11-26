#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "record.h"
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
#include "vex.h"

void autonomous(void) 
{
    if (manual && rojo)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("RM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        RM();
    }
    else if (manual && azul)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("BM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        BM();
    }
    else if (( rojo || azul || skills || slow || test))
    {
      int row = 1;
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(fontType::mono30);
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
        play();
      }
      else 
      {
        splay();
      }
    }
    else 
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(":( i sleep");
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("By: Pratham");
      
      while(!( rojo || azul || skills || slow || test))
      {
        if(Controller1.ButtonLeft.pressing())
        {
          /*
          turn right 90
          drive back 1
          drive forward 1
          */
        }

        if(Controller1.ButtonRight.pressing())
        {
          /*
          turn left 90
          drive back 1
          drive forward 1
          */
        }
      }

    }
    /*
    else
    {
        //Runs ambiguous auton that drops preload in goal zone
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("Ambi mode on");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        drive(-2, 100);
        drive(2, 100);
        flipOut();
    }
    */
}
#endif /* AUTONOMUS_H */