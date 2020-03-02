#include "main.h"

void play(void)
{
    std::ifstream inFile;
    double vel[5];
    if (rojo &! test)
    {
      inFile.open("r.txt");
    }
    else if (azul &! test)
    {
      inFile.open("b.txt");
    }
    else if (rojo && test)
    {
      inFile.open("rt.txt");
    }
    else if (azul && test)
    {
      inFile.open("bt.txt");
    }
    while(!inFile.eof())
    {
      for (int i = 0; i < 1500; i+= 1) 
      {
        inFile >> vel[0];
        LeftFrontMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        inFile >> vel[1];
        RightFrontMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        inFile >> vel[2];
        Lift.spin(vex::directionType::fwd, vel[2], vex::velocityUnits::pct);
        inFile >> vel[3];
        Tilt.spin(vex::directionType::fwd, vel[3], vex::velocityUnits::pct);
        inFile >> vel[4];
        LeftIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        vex::task::sleep(10);
      }
      inFile.close();
    }
    inFile.close();
}

void splay()
{
    std::ifstream inFile;
    double vel[5];
    if (!test)
    {
      inFile.open("s.txt");
    }
    else if (test)
    {
      inFile.open("st.txt");
    }
    
    while(!inFile.eof())
    {
      for (int i = 0; i < 6000; i+= 1) 
      {    
        inFile >> vel[0];
        LeftFrontMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        inFile >> vel[1];
        RightFrontMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        inFile >> vel[2];
        Lift.spin(vex::directionType::fwd, vel[2], vex::velocityUnits::pct);
        inFile >> vel[3];
        Tilt.spin(vex::directionType::fwd, vel[3], vex::velocityUnits::pct);
        inFile >> vel[4];
        LeftIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        vex::task::sleep(10);
      }
      inFile.close();
    }
    inFile.close();
}