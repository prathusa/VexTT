//GUI
#ifndef GUI_H
#define GUI_H

#include "vex.h"
#include "record.h"
#include "controls.h"
#include "manual.h"
#include "autonomous.h"

bool rec;
void pre_auton(void) 
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Calibrating");
    Gyro.calibrate(2000);
    Inertial.calibrate(2000);
    while(Inertial.isCalibrating())
    {
      vex::task::sleep(20);
    }
    Controller1.Screen.clearScreen();
    Brain.Screen.drawImageFromFile("1.png", 0, 0);

    if(Brain.Battery.capacity() > 60)
    {
      Brain.Screen.setFillColor(vex::green);
      Brain.Screen.setPenColor(vex::black);
    }
    else if(Brain.Battery.capacity() > 30)
    {
      Brain.Screen.setFillColor(vex::yellow);
      Brain.Screen.setPenColor(vex::black);
    }
    else
    {
      Brain.Screen.setFillColor(vex::red);
      Brain.Screen.setPenColor(vex::black);
    }
    Brain.Screen.print("Battery Percent%: %d", Brain.Battery.capacity());
    Brain.Screen.setFillColor(vex::black);
    Brain.Screen.setPenColor(vex::white);

    OS.menuCONFIG();	//Calls ACCESS_OS's menuCONFIG, the main reason why you downloaded this
	  OS.notificationHUD("Robot: OK");	//Sends message to driver

    one:
    vex::task::sleep(300);
    int xLastTouch = Brain.Screen.xPosition();
    int yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
        int x = Brain.Screen.xPosition();
        int y = Brain.Screen.yPosition();
        if(x > 410 && y < 70)
        {
            Brain.Screen.drawImageFromFile("2n.png", 0, 0);
            goto two;
        }
        else if(x < 240)
        {
          rojo = true;
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("RP Selected");
          autonController();
          autonBrain();
          Controller1.Screen.setCursor(2, 1);
          Controller1.Screen.print("By: PB & AB");
          goto end;
        }
        else if(x > 240)
        {
          azul = true;
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("BP Selected");
          autonController();
          autonBrain();
          Controller1.Screen.setCursor(2, 1);
          Controller1.Screen.print("By: PB & AB");
          goto end;
        }
      vex::task::sleep(20);
    }

    two:
    vex::task::sleep(300);
    xLastTouch = Brain.Screen.xPosition();
    yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
        int x = Brain.Screen.xPosition();
        int y = Brain.Screen.yPosition();
        if(x < 60 && y < 40)
        {
            Brain.Screen.clearScreen();
            Brain.Screen.drawImageFromFile("1.png", 0, 0);
            goto one;
        }
        else if( x < 240 && y < 120)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("3r.png", 0, 0);
          rojo = true;
          rec = false;
          goto three;
        }
        else if( x < 240 && y > 120)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("3b.png", 0, 0);
          rojo = false;
          azul = true;
          rec = false;
          goto three;
        }
        else if( x > 240 && y < 120)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("5r.png", 0, 0);
          rojo = true;
          rec = true;
          test = true;
          goto five;
        }
        else if( x > 240 && y > 120)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("5b.png", 0, 0);
          rojo = false;
          azul = true;
          rec = true;
          test = true;
          goto five;
        }
        vex::task::sleep(20);
    }

    three:
    vex::task::sleep(300);
    xLastTouch = Brain.Screen.xPosition();
    yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(x < 60 && y < 40)
      {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("2n.png", 0, 0);
          goto two;
      }
      else if( x < 240)
        {
          Brain.Screen.clearScreen();
          if(rojo)
          {
            Brain.Screen.drawImageFromFile("4r.png", 0, 0);
          }
          else 
          {
            Brain.Screen.drawImageFromFile("4b.png", 0, 0);
          }
          test = false;
          goto four;
        }
        else if( x > 240)
        {
          Brain.Screen.clearScreen();
         if(rojo)
          {
            Brain.Screen.drawImageFromFile("6r.png", 0, 0);
          }
          else 
          {
            Brain.Screen.drawImageFromFile("6b.png", 0, 0);
          }
          test = true;
          goto six;
        }
        vex::task::sleep(20);
    }

    four:
    vex::task::sleep(300);
    xLastTouch = Brain.Screen.xPosition();
    yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(x < 60 && y < 40)
      {
          Brain.Screen.clearScreen();
          if(rojo)
          {
            Brain.Screen.drawImageFromFile("3r.png", 0, 0);
          }
          else 
          {
            Brain.Screen.drawImageFromFile("3b.png", 0, 0);
          }
          goto three;
      }
      else if( x < 240)
        {
          Brain.Screen.clearScreen();
          manual = true;
          autonController();
          autonBrain();
          goto end;
        }
        else if( x > 240)
        {
          Brain.Screen.clearScreen();
          test = false;
          skills = true;
          autonController();
          autonBrain();
          goto end;
        }
        vex::task::sleep(20);
    }

    five:
    vex::task::sleep(300);
    xLastTouch = Brain.Screen.xPosition();
    yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(x < 60 && y < 40)
      {
          Brain.Screen.clearScreen();
          Brain.Screen.drawImageFromFile("2n.png", 0, 0);
          goto two;
      }
      else if( x < 240)
        {
          Brain.Screen.clearScreen();
          if(rojo)
          {
            Brain.Screen.drawImageFromFile("6r.png", 0, 0);
          }
          else 
          {
            Brain.Screen.drawImageFromFile("6b.png", 0, 0);
          }
          slow = true;
          goto six;
        }
        else if( x > 240)
        {
          Brain.Screen.clearScreen();
          if(rojo)
          {
            Brain.Screen.drawImageFromFile("6r.png", 0, 0);
          }
          else 
          {
            Brain.Screen.drawImageFromFile("6b.png", 0, 0);
          }
          slow = false;
          goto six;
        }
        vex::task::sleep(20);
    }

    six:
    vex::task::sleep(300);
    xLastTouch = Brain.Screen.xPosition();
    yLastTouch = Brain.Screen.yPosition();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        vex::task::sleep(20);
    }
    while(true)
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(x < 60 && y < 40)
      {
          Brain.Screen.clearScreen();
          if (rojo && !rec)
          {
            Brain.Screen.drawImageFromFile("3r.png", 0, 0);
            goto three;
          }
          else if (!rojo && !rec)
          {
            Brain.Screen.drawImageFromFile("3b.png", 0, 0);
            goto three;
          }
          else if (rojo && rec)
          {
            Brain.Screen.drawImageFromFile("5r.png", 0, 0);
            goto five;
          }
          else if (!rojo && rec)
          {
            Brain.Screen.drawImageFromFile("5b.png", 0, 0);
            goto five;
          }
      }
      else if( x < 240)
        {
          Brain.Screen.clearScreen();
          if(!rec)
          {
            skills = true;
            test = true;
            autonController();
            autonBrain();
          }
          else 
          {
            skills = true;
            record();
          }
          goto end;
        }
      else if( x > 240)
      {
        Brain.Screen.clearScreen();
        if(!rec)
        {
          skills = false;
          test = true;
          autonController();
          autonBrain();
        }
        else 
        {
          skills = false;
          record();
        }
        goto end;
      }
        vex::task::sleep(20);
    }

  end:
  vex::task::sleep(10);
}


#endif