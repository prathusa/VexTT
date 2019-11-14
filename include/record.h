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
          outFile << (l.velocity(vex::velocityUnits::pct)) << "\n";
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
          outFile << (l.velocity(vex::velocityUnits::pct)) << "\n";
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
          outFile << (l.velocity(vex::velocityUnits::pct)) << "\n";
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
          outFile << (l.velocity(vex::velocityUnits::pct)) << "\n";
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
#endif