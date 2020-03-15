#include "vex.h"

//flipout
void flipout()
{
  // d.spinFor(fwd, .7, rev, 100, velocityUnits::pct, false);
  intake.spinFor(directionType::fwd, 1.5, rev, 100, velocityUnits::pct);
  // intake.spin(directionType::rev, 100, pct);
  // robot.base.For(-.9);
}

//start lined up with 2 cubes in front 
void p3()
{

}

//start lined up with 2 cubes in front 
void p4()
{
  
}

//start lined up with 2 cubes in front 
void p5()
{
  
}

//start lined up to the right of red / left of blue, pre load off to the side (not being used)
void tp5()
{
  
}

//start lined up to the right of red / left of blue, pre load off to the side (not being used)
void p6()
{
  
}

void p7()
{
  
}

void p8()
{
  
}

void u3()
{
  
}

void u4()
{
  
}

void u5()
{
  flipout();
  intake.spin(directionType::rev, 100, pct);
  robot.base.setIntake();
  robot.base.For(3.2, 0);
  robot.base.setPrecise();
  intake.spinFor(directionType::rev, 1, rev, 100, velocityUnits::pct, false);
  robot.base.To(1, 0);
  robot.imu.To(90);
  robot.mech.setMech();
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(1, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
  robot.tilter.Stack();
  intake.spinFor(fwd, .5, rev, 60, velocityUnits::pct);
  robot.base.For(-.5, 90);
}

void u6()
{
  flipout();
  intake.spin(directionType::rev, 100, pct);
  robot.base.setIntake();
  robot.base.For(4, 0);
  robot.base.setPrecise();
  intake.spinFor(directionType::rev, 1, rev, 100, velocityUnits::pct, false);
  robot.base.To(1, 0);
  robot.imu.To(90);
  robot.mech.setMech();
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(1, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
  robot.tilter.Stack();
  intake.spinFor(fwd, .5, rev, 60, velocityUnits::pct);
  robot.base.For(-.5, 90);
}

void tu7()
{
  
}

void ttu7()
{
  
}

void u7()
{
  flipout();
  intake.spin(directionType::rev, 100, pct);
  robot.base.setIntake();
  robot.base.For(3.2, 0);
  robot.base.setPrecise();
  robot.base.To(1, 0);
  robot.mech.setMech();
  robot.mech.ToX(2);
  d.resetPosition();
  robot.base.setIntake();
  robot.base.For(1.8, 0);
  robot.base.setPrecise();
  robot.base.To(1, 0);
  robot.imu.To(90);
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(2, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
  robot.tilter.Stack();
  intake.spinFor(fwd, .5, rev, 60, velocityUnits::pct);
  robot.base.For(-.5, 90);
}

void u8()
{
  
}

void s18()
{
  
}

void s40()
{
  
}

void autonAmbi()
{
  
}