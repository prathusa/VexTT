#ifndef PLAY_H
#define PLAY_H\

#include "vex.h"
#include "manual.h"

void play(void)
{
    std::ifstream inFile;
    double vel[5];
    if (rojo &! test)
    {
      //inFile.open("r.txt");
    Brain.Timer.reset();
    double driveFwdDistance = 2.7;
    resetEncoders();
    Inertial.resetRotation();
    d.rotateFor(directionType::fwd, 1, rotationUnits::rev, 50, velocityUnits::pct, true);
    d.rotateFor(directionType::fwd, -1, rotationUnits::rev, 50, velocityUnits::pct, true);
    flipOut();
    d.rotateFor(directionType::fwd, -.5, rotationUnits::rev, 50, velocityUnits::pct, false);
    vex::task::sleep(200);
    //turnTo(0, true, 50);
    intake.spin(directionType::rev, 100, velocityUnits::pct);
    d.rotateFor(directionType::fwd, driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    //drive((-1.0/3)*driveFwdDistance);
    //d.rotateFor(directionType::fwd, (-1.0/3)*driveFwdDistance, rotationUnits::rev, 50, velocityUnits::pct, true);
    turnTo(120, true, 100);
    d.rotateFor(directionType::fwd, 3.2, rotationUnits::rev, 50, velocityUnits::pct, true);
    intake.stop();
    intake.spin(directionType::rev, 20, velocityUnits::pct);
    stack();
    //vex::task::sleep(200);
    fadeAway();
    intake.stop();
    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("%d ", Brain.Timer.time()); 
    }
    else if (azul &! test)
    {
      //inFile.open("b.txt");
      d.rotateFor(directionType::fwd, -2, rotationUnits::rev, 50, velocityUnits::pct, false);
      vex::task::sleep(4000);
      drive(2);
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

/*
void play(void)
{
    uint8_t buf[6000];
    if (rojo &! test)
    {
      Brain.SDcard.loadfile("r.txt", buf, 6000);
    }
    else if (!rojo &! test)
    {
      Brain.SDcard.loadfile("b.txt", buf, 6000);
    }
    else if (rojo && test)
    {
      Brain.SDcard.loadfile("rt.txt", buf, 6000);
    }
    else if (!rojo && test)
    {
      Brain.SDcard.loadfile("bt.txt", buf, 6000);
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
        
        vex::task::sleep(25/2);
    }
    
}
*/

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

/*
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
/*
void rp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("r.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void bp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("b.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void sp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("s.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(50);
    }
}

void rpt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("rt.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void bpt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("bt.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void spt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("st.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(50);
    }
}

void slowrp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slowr.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        //vex::task::sleep(13);
        vex::task::sleep(25/2);
    }
}

void slowbp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slowb.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void slowsp()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slows.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        //vex::task::sleep(13);
        vex::task::sleep(50);
    }
}

void slowrpt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slowrt.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        //vex::task::sleep(13);
        vex::task::sleep(25/2);
    }
}

void slowbpt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slowbt.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}

void slowspt()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("slowst.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        //vex::task::sleep(13);
        vex::task::sleep(50);
    }
}




/*

void autonRP()
{
    uint8_t buf[1500][5];
    for(int row = 0; row < 1500; row++)
    {
      Brain.SDcard.loadfile("dataR.txt", buf[row], 5);
    }
    
    for(int row = 0; row < 1500; row++)
    {
      l.spin(vex::directionType::fwd, buf[row][0] - 100, vex::velocityUnits::pct);
      r.spin(vex::directionType::fwd, buf[row][1] - 100, vex::velocityUnits::pct);
      Lift.spin(vex::directionType::fwd, buf[row][2] - 100, vex::velocityUnits::pct);
      Tilt.spin(vex::directionType::fwd, buf[row][3] - 100, vex::velocityUnits::pct);
      intake.spin(vex::directionType::fwd, buf[row][4] - 100, vex::velocityUnits::pct);
      vex::task::sleep(10);
    }
}

*/



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

/*
void newPlay()
{
  std::ifstream inFile;
  inFile.open("rn.txt");
  /*
  if (inFile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }
  *//*
  int vel[5];
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
*/

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------



//WOrking
/*
void autonRP()
{
    uint8_t buf[6000];
    Brain.SDcard.loadfile("rt.txt", buf, 6000);
    
    for (int i = 0; i < 6000; i+= 5) 
    {    
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(25/2);
    }
}


void autonCRP()
{
    uint8_t buf[7500];
    Brain.SDcard.loadfile("dataCRR.txt", buf, 7500);
    
    for (int i = 0; i < 7500; i+= 5) 
    {
        
        LeftFrontMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Lift.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        LeftIntake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, buf[i + 4] - 100, vex::velocityUnits::pct);
        
        vex::task::sleep(10);
    }
}

//For testing purposes only! Old code that works for sure
void oldERP()
{
    uint8_t buf[6000LL];
    //uint8_t buf[6000LL];
    Brain.SDcard.loadfile("dataERS.txt", buf, 6000LL);
    //Data stored in sets of 5:
    //1. LeftDrive (percent)
    //2. RightDrive (percent)
    //3. FBar (rpm)
    //4.  (0 for back, 2 for forward, 1 for not moving)
    //5. Flipper (percent)
    
    for (long long i = 0; i < 6000LL; i+= 4) {
        
        l.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        r.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        intake.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        vex::task::sleep(10);
    }
}

//For testing purposes only! Old code that works for sure
void oldRP()
{
    uint8_t buf[6000LL];
    //uint8_t buf[6000LL];
    Brain.SDcard.loadfile("dataRS.txt", buf, 6000LL);
    //Data stored in sets of 5:
    //1. LeftDrive (percent)
    //2. RightDrive (percent)
    //3. FBar (rpm)
    //4.  (0 for back, 2 for forward, 1 for not moving)
    //5. Flipper (percent)
    
    for (long long i = 0; i < 6000LL; i+= 4) {
        
        LeftFrontMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        LeftRearMotor.spin(vex::directionType::fwd, buf[i] - 100, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        RightRearMotor.spin(vex::directionType::fwd, buf[i + 1] - 100, vex::velocityUnits::pct);
        Tilt.spin(vex::directionType::fwd, buf[i + 2] - 100, vex::velocityUnits::pct);
        LeftIntake.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        RightIntake.spin(vex::directionType::fwd, buf[i + 3] - 100, vex::velocityUnits::pct);
        vex::task::sleep(10);
    }
}
*/
#endif /* AUTONRP_H */