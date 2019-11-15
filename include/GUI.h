#ifndef GUI_H
#define GUI_H

#include "vex.h"
#include "record.h"
#include "controls.h"
#include "manual.h"
#include "autonomus.h"

bool rec;
void pre_auton(void) 
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Select Auton");
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
          skills = false;
          slow = false;
          test = false; 
          manual = false;
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("RP Selected");
          Controller1.Screen.clearScreen();
          Controller1.Screen.setCursor(1, 1);
          Controller1.Screen.print("RP Selected");
          Controller1.Screen.setCursor(2, 1);
          Controller1.Screen.print("By: PB & AB");
          goto end;
        }
        else if(x > 240)
        {
          rojo = false;
          azul = true;
          skills = false;
          slow = false;
          test = false; 
          manual = false;
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("BP Selected");
          Controller1.Screen.clearScreen();
          Controller1.Screen.setCursor(1, 1);
          Controller1.Screen.print("BP Selected");
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
          goto end;
        }
        else if( x > 240)
        {
          Brain.Screen.clearScreen();
          test = false;
          skills = true;
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













//Double Sided Auton (Red Side and Blue Side)
/*
int allSpeed = 127; //Speed for all motors in auto mode.
int auton = -1;

void askPlatform()
{
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.drawRectangle(0, 0, 240, 230, red);
    Brain.Screen.printAt(80,130,"RS");
    Brain.Screen.drawRectangle(240, 0, 240, 230, blue);
    Brain.Screen.printAt(290,130,"BS");
}

void pre_auton(void) 
{
    int xLastTouch = Brain.Screen.xPosition();
    int yLastTouch = Brain.Screen.yPosition();
    askPlatform();
    bool i = true;
    while(i)
    {
        //-----------------------------Touch Check
        if(Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() != xLastTouch && Brain.Screen.yPosition() != yLastTouch)
        {
            auton = 0;
            i = false;
        }
        else if(240 < Brain.Screen.xPosition() && Brain.Screen.xPosition() != xLastTouch && Brain.Screen.yPosition() != yLastTouch)
        {
            auton = 1;
            i = false;
        }
        vex::task::sleep(20);
    }
    vex::task::sleep(300);
    
    if(auton == 0)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("RS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("RS Selected");
    }
    else if(auton == 1)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("BS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("BS Selected");
    }
}

*/

//------------------------------------------------------------------------------------------------------

//Octuple Sided Auton(Plat, Non-Plat)
/*
bool debugMode = false;
bool testMode = false;
int allSpeed = 90; //Speed for all motors in auto mode.
int auton = 0;
int plat = 1;

void askPosition()
{
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.drawRectangle(0, 0, 240, 115, red); //RFS
    Brain.Screen.printAt(90,70,"RFS");
    Brain.Screen.drawRectangle(240, 0, 240, 115, blue); //BFS
    Brain.Screen.printAt(330,70,"BFS");
    Brain.Screen.drawRectangle(0, 115, 240, 115, red); //RBS
    Brain.Screen.printAt(90,180,"RBS");
    Brain.Screen.drawRectangle(240, 115, 240, 115, blue); //BBS
    Brain.Screen.printAt(330,180,"BBS");
}

void askPlatform()
{
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.drawRectangle(0, 0, 240, 230, yellow); //Platform
    Brain.Screen.printAt(80,130,"Plat");
    Brain.Screen.drawRectangle(240, 0, 240, 230, red); //No-Platform
    Brain.Screen.printAt(290,130,"No Plat");
}


void pre_auton(void) 
{
    LeftFrontMotor.stop(brakeType::brake);
    RightFrontMotor.stop(brakeType::brake);
    RightRearMotor.stop(brakeType::brake);
    LeftRearMotor.stop(brakeType::brake);
    int xLastTouch = Brain.Screen.xPosition();
    int yLastTouch = Brain.Screen.yPosition();
    askPlatform();
    while(Brain.Screen.xPosition() == xLastTouch && Brain.Screen.yPosition() == yLastTouch)
    {
        if(TestMode.pressing() == 1)
        {
            testMode = true;
        }
        if(DebugMode.pressing() == 1)
        {
            debugMode = true;
        }
        vex::task::sleep(20);
    }
    bool i = true;
    while(i)
    {
        //-----------------------------Touch Check
        if(Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() != xLastTouch && Brain.Screen.yPosition() != yLastTouch)
        {
            plat = 0;
            vex::task::sleep(300);
            i = false;
        }
        else if(240 < Brain.Screen.xPosition() && Brain.Screen.xPosition() != xLastTouch && Brain.Screen.yPosition() != yLastTouch)
        {
            plat = 1;
            vex::task::sleep(300);
            i = false;
        }
        //------------------------------Controller Check
        else if(Controller1.ButtonY.pressing() && Controller1.ButtonLeft.pressing())
        {
            plat = 0;
            i = false;
        }
        else if(Controller1.ButtonY.pressing() && Controller1.ButtonRight.pressing())
        {
            plat = 1;
            i = false;
        }
        vex::task::sleep(20);
    }
    int xLastTouch2 = Brain.Screen.xPosition();
    int yLastTouch2 = Brain.Screen.yPosition();
    askPosition();
    while((Brain.Screen.xPosition() == xLastTouch2 && Brain.Screen.yPosition() == yLastTouch2) || Controller1.ButtonB.pressing())
    {
        vex::task::sleep(20);
    }
    bool k = true;
    while(k)
    {
        //-----------------------------Touch Check
        if(Brain.Screen.xPosition() < 240 && Brain.Screen.yPosition() < 115 && Brain.Screen.xPosition() > 0)
        {
            auton = 1;
            k = false;
        }
        else if(240 < Brain.Screen.xPosition() && Brain.Screen.yPosition() < 115 && Brain.Screen.xPosition() > 0)
        {
            auton = 2;
            k = false;
        }
        else if(Brain.Screen.xPosition() < 240 && 115 < Brain.Screen.yPosition() && Brain.Screen.xPosition() > 0)
        {
            auton = 3;
            k = false;
        }
        else if(240 < Brain.Screen.xPosition() && 115 < Brain.Screen.yPosition() && Brain.Screen.xPosition() > 0)
        {
            auton = 4;
            k = false;
        } 
        //------------------------------Controller Check
        else if(Controller1.ButtonY.pressing())
        {
            if(Controller1.ButtonL2.pressing())
            {
                auton = 1;
                k = false;
            }
            else if(Controller1.ButtonR2.pressing())
            {
                auton = 2;
                k = false;
            }
            else if(Controller1.ButtonL1.pressing())
            {
                auton = 3;
                k = false;
            }
            else if(Controller1.ButtonR1.pressing())
            {
                auton = 4;
                k = false;
            }
        }
    }
    
    if(auton == 1)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("RFS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("RFS Selected");
    }
    else if(auton == 2)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("BFS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("BFS Selected");
    }
    else if(auton == 3)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("RBS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("RBS Selected");
    }
    else if(auton == 4)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.print("BBS Selected");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("BBS Selected");
    }
   
}

void autonSorter(int autonNum, int platNum)
{
    if(autonNum == 1 && platNum == 0)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running RFS");
        autoRFS();
        drive(-.7);
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnLeft(90);
        drive(2.7);
        IntakeMotor.stop();
        turnLeft(90);
        drive(5);
        /*
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnRight(95);
        driveFwd(2.7);
        vex::task::sleep(1500);
        IntakeMotor.stop();
        driveBwd(.5);
        vex::task::sleep(300);
        turnRight(105);
        driveFwd(5);
        vex::task::sleep(3000);
        */
        /*
    }
    else if(autonNum == 2 && platNum == 0)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running BFS");
        autoBFS();
        drive(-.7);
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnLeft(90);
        drive(-2.7);
        IntakeMotor.stop();
        drive(-.3);
        turnLeft(90);
        drive(5);
    }
    else if(autonNum == 3 && platNum == 0)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running RBS");
        autoRBS();
        //Add code that goes to platform
    }
    else if(autonNum == 4 && platNum == 0)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running BBS");
        autoBBS();
        //Add code that goes to platform
    }
    else if(autonNum == 1 && platNum == 1)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running RFS");
        autoRFS();
        turnLeft(45);
        drive(1.5);
        drive(-1.5);
        turnRight(45);
        drive(-.7);
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnRight(90);
        drive(-2.7);
        IntakeMotor.stop();
    }
    else if(autonNum == 2 && platNum == 1)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running BFS No Plat");
        autoBFS();
        drive(-.7);
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnLeft(90);
        drive(2.7);
        IntakeMotor.stop();
    }
    else if(autonNum == 3 && platNum == 1)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running RBS No Plat");
        autoRBS();
    }
    else if(autonNum == 4 && platNum == 1)
    {
        
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running BBS No Plat");
        autoBBS();
        /*
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Running RFS");
        autoRFS();
        IntakeMotor.spin(directionType::fwd,127,velocityUnits::rpm);
        turnRight(95);
        driveFwd(2.7);
        vex::task::sleep(1500);
        IntakeMotor.stop();
        driveBwd(.5);
        vex::task::sleep(300);
        turnRight(105);
        driveFwd(5);
        vex::task::sleep(3000);
        turnLeft(90);
        driveFwd(1.5);
        vex::task::sleep(800);
        */
        /*
    }
    else if(Controller1.ButtonUp.pressing() && Controller1.ButtonY.pressing())
    {
        skillsRun();
    }
    else
    {
        //Doesn't run Auton
        Controller1.Screen.clearScreen();
        Controller1.Screen.print(":( i sleep");
    }
}

void autonomous(void) 
{
    LeftFrontMotor.stop(brakeType::hold);
    RightFrontMotor.stop(brakeType::hold);
    RightRearMotor.stop(brakeType::hold);
    LeftRearMotor.stop(brakeType::hold);
    resetRot();
    autonSorter(auton, plat);
}

*/


#endif