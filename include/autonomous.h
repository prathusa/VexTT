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
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("red");
      Controller1.Screen.print(rojo);
      Controller1.Screen.print(" sk");
      Controller1.Screen.print(skills);
      Controller1.Screen.print(" sl");
      Controller1.Screen.print(slow);
      Controller1.Screen.print(" test");
      Controller1.Screen.print(test);
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
}
#endif /* AUTONOMUS_H */