#ifndef PLAY_H
#define PLAY_H\

#include "vex.h"

void play(void)
{
    std::ifstream inFile;
    double vel[5];
    if (rojo &! test)
    {
      inFile.open("r.txt");
    }
    else if (!rojo &! test)
    {
      inFile.open("b.txt");
    }
    else if (rojo && test)
    {
      inFile.open("rt.txt");
    }
    else if (!rojo && test)
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
    uint8_t buf[6000];
    if (!test)
    {
      Brain.SDcard.loadfile("s.txt", buf, 6000);
    }
    else if (test)
    {
      Brain.SDcard.loadfile("st.txt", buf, 6000);
    }
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        LeftFrontMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        LeftIntake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(50);
    }
}


void newPlay()
{
  std::ifstream inFile;
  inFile.open("rn.txt");
  double vel[5];
  while(!inFile.eof())
  {
    for (int i = 0; i < 1500; i+= 1) 
    {    
        //inFile.open("rn.txt");
        inFile >> vel[0];
        //vel[0] = inFile.get();
        LeftFrontMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, vel[0], vex::velocityUnits::pct);
        inFile >> vel[1];
        //vel[1] = inFile.get();
        RightFrontMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, vel[1], vex::velocityUnits::pct);
        inFile >> vel[2];
        //vel[2] = inFile.get();
        Lift.spin(vex::directionType::fwd, vel[2], vex::velocityUnits::pct);
        inFile >> vel[3];
        //vel[3] = inFile.get();
        Tilt.spin(vex::directionType::fwd, vel[3], vex::velocityUnits::pct);
        inFile >> vel[4];
        //vel[4] = inFile.get();
        LeftIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, vel[4], vex::velocityUnits::pct);
        //inFile.close();
        vex::task::sleep(10);
    }
    inFile.close();
  }
  inFile.close();
}

#endif /* AUTONRP_H */