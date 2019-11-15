//Autonomus Recording Code
#ifndef RECORD_H
#define RECORD_H

#include "vex.h" 
#include "controls.h"
#include "manual.h"

void record(void)
{
    driveSpeedFactor = 2;
    std::ofstream outFile;
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    if(skills)
    {
      outFile.open("st.txt");
      if(slow)
      {
        for (int i = 0; i < 6000; i+= 1) 
        {
          controls();
          outFile << l.velocity(vex::velocityUnits::pct) << "\n";
          outFile << r.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Lift.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Tilt.velocity(vex::velocityUnits::pct) << "\n";
          outFile << intake.velocity(vex::velocityUnits::pct) << "\n";
          vex::task::sleep(10);
        }
        outFile.close();
      }
      else
      {
        for (int i = 0; i < 7200; i+= 1) 
        {
          controls();
          outFile << l.velocity(vex::velocityUnits::pct) << "\n";
          outFile << r.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Lift.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Tilt.velocity(vex::velocityUnits::pct) << "\n";
          outFile << intake.velocity(vex::velocityUnits::pct) << "\n";
          vex::task::sleep(12);
        }
        outFile.close();
      }
    }
    else if(slow)
    {
      if(rojo)
      {
        outFile.open("rt.txt");
      }
      else if(azul)
      {
        outFile.open("bt.txt");
      }
      for (int i = 0; i < 2250; i+= 1) 
      {
          controls();
          outFile << l.velocity(vex::velocityUnits::pct) << "\n";
          outFile << r.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Lift.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Tilt.velocity(vex::velocityUnits::pct) << "\n";
          outFile << intake.velocity(vex::velocityUnits::pct) << "\n";
          vex::task::sleep(15);
      }
      outFile.close();
    }
    else
    {
      if(rojo)
      {
        outFile.open("rt.txt");
      }
      else if(azul)
      {
        outFile.open("bt.txt");
      }
      for (int i = 0; i < 1500; i+= 1) 
      {
          controls();
          outFile << l.velocity(vex::velocityUnits::pct) << "\n";
          outFile << r.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Lift.velocity(vex::velocityUnits::pct) << "\n";
          outFile << Tilt.velocity(vex::velocityUnits::pct) << "\n";
          outFile << intake.velocity(vex::velocityUnits::pct) << "\n";
          vex::task::sleep(10);
      }
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void getData(void)
{
    std::ofstream outFile;
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    outFile.open("data.txt");
    for (int i = 0; i < 4000; i+= 1) 
    {
      controls();
      outFile << l.velocity(vex::velocityUnits::pct) << "\n";
      outFile << l.position(rotationUnits::rev) << "\n";
      outFile << r.velocity(vex::velocityUnits::pct) << "\n";
      outFile << r.position(rotationUnits::rev) << "\n";
      vex::task::sleep(1);
    }
    outFile.close();      
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}


/*
void record(void)
{
    //tank = false;
    driveSpeedFactor = 1.5;
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    if(skills)
    {
      if(slow)
      {
        for (int i = 0; i < 6000; i+= 5) 
        {
          controls();
          data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
          data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
          data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
          data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
          data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);

          vex::task::sleep(75);
        }
      }
      else
      {
        for (int i = 0; i < 6000; i+= 5) 
        {
          controls();
          data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
          data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
          data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
          data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
          data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);

          vex::task::sleep(50);
        }
      }
      Brain.SDcard.savefile("st.txt", data, 6000);
    }
    else if(slow)
    {
      for (int i = 0; i < 6000; i+= 5) 
      {
          controls();
          data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
          data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
          data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
          data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
          data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);

          vex::task::sleep(17);
      }
      if(rojo)
      {
        Brain.SDcard.savefile("rt.txt", data, 6000);
      }
      else
      {
        Brain.SDcard.savefile("bt.txt", data, 6000);
      }
    }
    else
    {
      for (int i = 0; i < 6000; i+= 5) 
      {
        controls();
          data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
          data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
          data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
          data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
          data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);

          vex::task::sleep(25/2);
      }
      if(rojo)
      {
        Brain.SDcard.savefile("rt.txt", data, 6000);
      }
      else
      {
        Brain.SDcard.savefile("bt.txt", data, 6000);
      }
    }
    
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void newRecord()
{
    std::ofstream outFile;
    outFile.open("rn.txt");
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    for (int i = 0; i < 1500; i+= 1) 
    {
        controls();
        outFile << (l.velocity(vex::velocityUnits::pct)) << "\n";
        outFile << r.velocity(vex::velocityUnits::pct) << "\n";
        outFile << Lift.velocity(vex::velocityUnits::pct) << "\n";
        outFile << Tilt.velocity(vex::velocityUnits::pct) << "\n";
        outFile << intake.velocity(vex::velocityUnits::pct) << "\n";
        vex::task::sleep(10);
    }
    outFile.close();
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");
}

/*
void slowrecord(int file)
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(25);
    }
    if (file == 6)
    {
      Brain.SDcard.savefile("rt.txt", data, 6000);
    }
    else if (file == 7)
    {
      Brain.SDcard.savefile("bt.txt", data, 6000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void srecord(int sfile)
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(50);
    }
    Brain.SDcard.savefile("st.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void slowsrecord(int file)
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(100);
    }
    Brain.SDcard.savefile("slowst.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void rrt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(25/2);
    }
    Brain.SDcard.savefile("rt.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void brt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(13);
    }
    Brain.SDcard.savefile("bt.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void srt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(50);
    }
    Brain.SDcard.savefile("st.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void slowrrt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(25);
    }
    Brain.SDcard.savefile("slowrt.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void slowbrt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(25);
    }
    Brain.SDcard.savefile("slowbt.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}

void slowsrt()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    for(int count = 5; count > 0; count--)
    {
      Controller1.Screen.clearLine(1);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(count);
      vex::task::sleep(1000);
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 5) 
    {
        controls(1);
        data[i] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[i + 4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(100);
    }
    Brain.SDcard.savefile("slowst.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}











//Bad
/*
void autonRR()
{
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Recording");
    uint8_t data[1500][5];
    int driveSpeedFactor = 1;  
    for (int row = 0; row < 1500; row++) 
    {
        // -----------------------------Tilt Control
        if(Controller1.ButtonY.pressing())
        {
          int old = driveSpeedFactor;
          driveSpeedFactor = 4;
          Tilt.rotateFor(directionType::fwd, 1.35, rotationUnits::rev, 60, velocityUnits::pct);
          driveSpeedFactor = old;
        }
        else if(Controller1.ButtonX.pressing())
        {
          Tilt.spin(directionType::rev, 30, percentUnits::pct);
        }
        else
        {
          Tilt.stop(brake);
        }
        
        //Tilt.spin(vex::directionType::fwd, Controller1.Axis2.value()/6, vex::velocityUnits::pct);

        //Tank Control
        
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 

                

        // -----------------------------Robot Sensitivity Change
        if(Controller1.ButtonB.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced");
        }
        else if(Controller1.ButtonA.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 1; //Resets the drive speed to normal
        }

        // -----------------------------Intake Control
        if(Controller1.ButtonR2.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing())
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 60, velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing())
        {
            Lift.spin(directionType::rev, 60, velocityUnits::pct);
        }
        else
        {
          Lift.setBrake(hold);
          Lift.stop();
        }

        
        data[row][0] = (uint8_t) (l.velocity(vex::velocityUnits::pct) + 100);
        data[row][1] = (uint8_t) (r.velocity(vex::velocityUnits::pct) + 100);
        data[row][2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        data[row][3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        data[row][4] = (uint8_t) (intake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(10);
    }
    uint8_t save[7500];
    for(int row = 0; row < 7500; row+= 5)
    {
      save[row] = data[row][0];
      save[row+1] = data[row][1];
      save[row+2] = data[row][2];
      save[row+3] = data[row][3];
      save[row+4] = data[row][4];
    }
    Brain.SDcard.savefile("dataR.txt", save, 7500);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Complete!");  
}


*/














































































//Works
/*
void autonRR()
{
    uint8_t data[6000];
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Recording");
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 6000; i+= 4) 
    {
       // -----------------------------Tilt Control
        if(Controller1.ButtonY.pressing())
        {
          int old = driveSpeedFactor;
          driveSpeedFactor = 4;
          Tilt.rotateFor(directionType::fwd, 1.35, rotationUnits::rev, 60, velocityUnits::pct);
          driveSpeedFactor = old;
        }
        else if(Controller1.ButtonX.pressing())
        {
          Tilt.spin(directionType::rev, 30, percentUnits::pct);
        }
        else
        {
          Tilt.stop(brake);
        }
        
        //Tilt.spin(vex::directionType::fwd, Controller1.Axis2.value()/6, vex::velocityUnits::pct);

        //Tank Control
        
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 

                

        // -----------------------------Robot Sensitivity Change
        if(Controller1.ButtonB.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced");
        }
        else if(Controller1.ButtonA.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 1; //Resets the drive speed to normal
        }

        // -----------------------------Intake Control
        if(Controller1.ButtonR2.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing())
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 60, velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing())
        {
            Lift.spin(directionType::rev, 60, velocityUnits::pct);
        }
        else
        {
          Lift.setBrake(hold);
          Lift.stop();
        }

        
        data[i] = (uint8_t) (LeftFrontMotor.velocity(vex::velocityUnits::pct) + 100);
        data[i + 1] = (uint8_t) (RightFrontMotor.velocity(vex::velocityUnits::pct) + 100);
        data[i + 2] = (uint8_t) (Lift.velocity(vex::velocityUnits::pct) + 100);
        //data[i + 3] = (uint8_t) (Tilt.velocity(vex::velocityUnits::pct) + 100);
        //data[i + 4] = (uint8_t) (LeftIntake.velocity(vex::velocityUnits::pct) + 100);
        data[i + 3] = (uint8_t) (LeftIntake.velocity(vex::velocityUnits::pct) + 100);
        vex::task::sleep(10);
    }
    Brain.SDcard.savefile("dataR.txt", data, 6000);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording complete!");  
}


*/



























/*
void autonCRR()
{
    uint32_t NUM_VALUES = 1500;
    uint32_t AUTON_TIME = 15000;
    std::vector<uint8_t> stuff;
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording");
    Brain.Screen.print("values set");
    Brain.Screen.render();
    int driveSpeedFactor = 1;  
    for (int i = 0; i < 7500; i+= 5) 
    {
       //Add driver code here (don't include the while loop):
        if(Controller1.ButtonY.pressing())
        {
          int old = driveSpeedFactor;
          driveSpeedFactor = 4;
          Tilt.rotateFor(directionType::fwd, 1.35, rotationUnits::rev, 60, velocityUnits::pct);
          driveSpeedFactor = old;
        }
        else if(Controller1.ButtonX.pressing())
        {
          Tilt.spin(directionType::rev, 30, percentUnits::pct);
        }
        else
        {
          Tilt.stop(brake);
        }
        
        //Tilt.spin(vex::directionType::fwd, Controller1.Axis2.value()/6, vex::velocityUnits::pct);

        //Tank Control
        
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 

                

        // -----------------------------Robot Sensitivity Change
        if(Controller1.ButtonB.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 2; //Makes robot slower
            Controller1.Screen.setCursor(1,1);
            Controller1.Screen.print("Speed Reduced");
        }
        else if(Controller1.ButtonA.pressing())
        {
            Controller1.Screen.clearScreen();
            driveSpeedFactor = 1; //Resets the drive speed to normal
        }

        // -----------------------------Intake Control
        if(Controller1.ButtonR2.pressing())
        {
            LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
            RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing())
        {
            LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
            RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else
        {
          LeftIntake.stop(brakeType::brake);
          RightIntake.stop(brakeType::brake);
        }

        // -----------------------------Lift Control
        if(Controller1.ButtonUp.pressing())
        {
            Lift.spin(directionType::fwd, 60, velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing())
        {
            Lift.spin(directionType::rev, 60, velocityUnits::pct);
        }
        else
        {
          Lift.setBrake(hold);
          Lift.stop();
        }
        
        stuff.push_back((uint8_t) (LeftFrontMotor.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (RightFrontMotor.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (Lift.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (Tilt.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (LeftIntake.velocity(vex::velocityUnits::pct)+100));
        vex::task::sleep(10);
    }
    /*
    for (long long i = 0; i < 6000LL; i+= 4) 
    {
       
       //insert driver control here:

        
        stuff.push_back((uint8_t) (LeftFrontMotor.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (RightFrontMotor.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (FBar1.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (Claw.velocity(vex::velocityUnits::pct)+100));
        /*data[i] = (uint8_t) (LeftDrive.velocity(vex::velocityUnits::pct)+100);
        data[i + 1] = (uint8_t) (RightDrive.velocity(vex::velocityUnits::pct)+100);
        data[i + 2] = (uint8_t) (Flywheel1.velocity(vex::velocityUnits::pct)+100);
        data[i + 3] = (uint8_t) (Intake.velocity(vex::velocityUnits::pct)+100);
        data[i + 4] = (uint8_t) (Flipper.velocity(vex::velocityUnits::pct)+100);*/
        /*
        vex::task::sleep(10);
    }
    */
    /*
    Brain.SDcard.savefile("dataCRR.txt", stuff.data(), 7500);
    Brain.Screen.print("saved dataCRR");
    Brain.Screen.render();
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Recording complete!");  
    
}


void oldERR()
{
    uint32_t NUM_VALUES = 1500;
    uint32_t AUTON_TIME = 15000;
    //uint8_t *data = record();
    std::vector<uint8_t> stuff;
    //uint8_t data[7500LL]; //full list of values, length 1500 * num_motors
    Brain.Screen.print("values set");
    Brain.Screen.render();
    int clawSpeedPCT = 50;
    int driveSpeedFactor = 1;
    int armSpeedPCT = 127;
    for (long long i = 0; i < 6000LL; i+= 4) {
       //Drive Control
        //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 
                

        // -----------------------------Robot Sensitivity Change
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 2; //Changes the drive speed to half
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Resets the drive speed to normal
        }
        
        //Four Bar Control
        if(Controller1.ButtonR2.pressing()) { //If button up is pressed...
            //...Spin the arm motor forward.
            LeftIntake.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
            RightIntake.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
           
        }
        else if(Controller1.ButtonL2.pressing()) { //If the down button is pressed...
            //...Spin the arm motor backward.
             LeftIntake.spin(vex::directionType::rev,  armSpeedPCT, vex::velocityUnits::pct);
             RightIntake.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      
            
        }
        else { //If the the up or down button is not pressed...
            //...Stop the arm motor.
              LeftIntake.stop(vex::brakeType::brake);        
              RightIntake.stop(vex::brakeType::brake);        
        }
        
        
        
        
        //Claw Control
        if(Controller1.ButtonR1.pressing()) { //If the A button is pressed...
            //...Spin the claw motor forward.
            Tilt.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL1.pressing()) { //If the Y button is pressed...
            //...Spin the claw motor backward.
            Tilt.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { //If the B button is pressed...        
            //...Stop the claw motor.
            Tilt.stop(vex::brakeType::hold);        
        }

        //Claw Control
        if(Controller1.ButtonUp.pressing()) { //If the A button is pressed...
            //...Spin the claw motor forward.
            Lift.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) { //If the Y button is pressed...
            //...Spin the claw motor backward.
            Lift.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { //If the B button is pressed...        
            //...Stop the claw motor.
            Lift.stop(vex::brakeType::hold);        
        }

        // -----------------------------Controller Screen Manipulation
        
        /**
        Prints the motor speed to the controller screen and notifies the driver if Aim Mode is on.
        **/
        /*
        stuff.push_back((uint8_t) (l.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (r.velocity(vex::velocityUnits::pct)+100));
        //stuff.push_back((uint8_t) (Tilt.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (Lift.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (intake.velocity(vex::velocityUnits::pct)+100));
        vex::task::sleep(10);
    }
    Brain.SDcard.savefile("dataERS.txt", stuff.data(), 6000LL);
    Brain.Screen.print("saved data");
    Brain.Screen.render();
}

void oldRR()
{
    uint32_t NUM_VALUES = 1500;
    uint32_t AUTON_TIME = 15000;
    //uint8_t *data = record();
    std::vector<uint8_t> stuff;
    //uint8_t data[7500LL]; //full list of values, length 1500 * num_motors
    Brain.Screen.print("values set");
    Brain.Screen.render();
    int clawSpeedPCT = 50;
    int driveSpeedFactor = 1;
    int armSpeedPCT = 127;
    for (long long i = 0; i < 6000LL; i+= 4) {
       //Drive Control
        //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
        LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/driveSpeedFactor, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/driveSpeedFactor, vex::velocityUnits::pct); 
                

        // -----------------------------Robot Sensitivity Change
        if(Controller1.ButtonB.pressing())
        {
            driveSpeedFactor = 2; //Changes the drive speed to half
        }
        else if(Controller1.ButtonA.pressing())
        {
            driveSpeedFactor = 1; //Resets the drive speed to normal
        }
        
        //Four Bar Control
        if(Controller1.ButtonR2.pressing()) { //If button up is pressed...
            //...Spin the arm motor forward.
            LeftIntake.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
            RightIntake.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
           
        }
        else if(Controller1.ButtonL2.pressing()) { //If the down button is pressed...
            //...Spin the arm motor backward.
             LeftIntake.spin(vex::directionType::rev,  armSpeedPCT, vex::velocityUnits::pct);
             RightIntake.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      
            
        }
        else { //If the the up or down button is not pressed...
            //...Stop the arm motor.
              LeftIntake.stop(vex::brakeType::brake);        
              RightIntake.stop(vex::brakeType::brake);        
        }
        
        
        
        
        //Claw Control
        if(Controller1.ButtonR1.pressing()) { //If the A button is pressed...
            //...Spin the claw motor forward.
            Tilt.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL1.pressing()) { //If the Y button is pressed...
            //...Spin the claw motor backward.
            Tilt.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { //If the B button is pressed...        
            //...Stop the claw motor.
            Tilt.stop(vex::brakeType::hold);        
        }

        //Claw Control
        if(Controller1.ButtonUp.pressing()) { //If the A button is pressed...
            //...Spin the claw motor forward.
            Lift.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonDown.pressing()) { //If the Y button is pressed...
            //...Spin the claw motor backward.
            Lift.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
        }
        else { //If the B button is pressed...        
            //...Stop the claw motor.
            Lift.stop(vex::brakeType::hold);        
        }

        // -----------------------------Controller Screen Manipulation
        
        /**
        Prints the motor speed to the controller screen and notifies the driver if Aim Mode is on.
        **/
        /*
        stuff.push_back((uint8_t) (LeftFrontMotor.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (RightFrontMotor.velocity(vex::velocityUnits::pct)+100));
        //stuff.push_back((uint8_t) (Tilt.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (Lift.velocity(vex::velocityUnits::pct)+100));
        stuff.push_back((uint8_t) (LeftIntake.velocity(vex::velocityUnits::pct)+100));
        vex::task::sleep(10);
    }
    Brain.SDcard.savefile("dataRS.txt", stuff.data(), 6000LL);
    Brain.Screen.print("saved data");
    Brain.Screen.render();
}
*/
#endif