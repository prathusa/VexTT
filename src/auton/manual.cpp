#include "main.h"

/* Initial 15 second begginning of the match autonomous ideas/plans
  Start the bot with the intake facing the wall in order ot avoid turning the bot over 90 degrees.
    Pseudo code:
    _____attempting to score the corner goal_____ (3 alliance & 0 opponent balls in goal)
    -drive bwd
    -turn to goal 45 degrees
    -intake on
    -intake both balls that are alliance colors
    -start shooting the balls into the hoop
    -while shooting, intake the opponent color ball
    -drive bwd
    _____attempting to score the mid goal_____ (1 alliance & 0 opponent balls in goal)
    -turn to 0 degrees
    -strafe to mid goal
      -(optional) while strafing outtake the opponent color ball from the bot which was removed from the previous goal
    -drive fwd
    -intake both balls in the mid goal and shoot out 1 ball back into the goal
    _____attempting to score the third goal_____ (2 alliance & 0 opponent balls in goal)
    -drive bwd
    -strafe to 3rd goal
      -(optional) while strafing outtake the opponent color ball from the bot which was removed from the previous goal
    -turn to goal -45 degrees
    -intake all balls in the goal & the one in front of the goal
    -shoot out 2 of the balls into the goal
    -drive bwd

  Alternatively, starting the bot facing the mid goal to shoot the ball into as soon as autonomous round starts could also be beneficial.
  Pseudo code:
    _____attempting to score the mid goal_____ (2 alliance & 1 opponent balls in goal)
    -strafe to line up with goal
    -shoot the preload
    _____attempting to score the corner goal_____ (2 alliance & 0 opponent balls in goal)
    -strafe further out
    -turn to corner goal 135 degrees  
    -intake on
    -intake both balls that are alliance colors
    -start shooting the balls into the hoop
    -while shooting, intake the opponent color ball
    -drive bwd
    _____attempting to score the mid goal_____ (2 alliance & 0 opponent balls in goal)
    -turn to 90 degrees
    -strafe to mid goal
    -drive fwd
    -intake 2 balls in the mid goal and shoot out 1 ball back into the goal
    _____attempting to score the third goal_____ (2 alliance & 0 opponent balls in goal)
    -drive bwd
    -strafe to 3rd goal
    -turn to goal -45 degrees
    -intake all balls in the goal & the one in front of the goal
    -shoot out 2 of the balls into the goal
    -drive bwd
  
  A consistant version can first shoot the alliance color ball into the hoop scoring it for the colored alliance and then descore the opponent color.
  A very basic auton could just descore all of the balls from alliance tower(s) which would remove the opponent's tic tac toe line advantage.
  Making a program that does all 3 towers will be difficult because of time and alliance constraints.


*/

void p3()
{

}

void p4()
{
  
}

void p5()
{
  
}

void tp5()
{
  
}

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
  // robot.base.setIntake();
  robot.base.For(3.2, 0);
  // robot.base.setPrecise();
  intake.spinFor(directionType::rev, 1, rev, 100, velocityUnits::pct, false);
  robot.base.To(1, 0);
  robot.imu.To(90);
  // robot.mech.setMech();
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(1, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
  intake.spinFor(fwd, .5, rev, 60, velocityUnits::pct);
  robot.base.For(-.5, 90);
}

void u6()
{
  flipout();
  intake.spin(directionType::rev, 100, pct);
  // robot.base.setIntake();
  robot.base.For(4, 0);
  // robot.base.setPrecise();
  intake.spinFor(directionType::rev, 1, rev, 100, velocityUnits::pct, false);
  robot.base.To(1, 0);
  robot.imu.To(90);
  // robot.mech.setMech();
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(1, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
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
  // robot.base.setIntake();
  robot.base.For(3.2, 0);
  // robot.base.setPrecise();
  robot.base.To(1, 0);
  // robot.mech.setMech();
  robot.mech.ToX(2);
  d.resetPosition();
  // robot.base.setIntake();
  robot.base.For(1.8, 0);
  // robot.base.setPrecise();
  robot.base.To(1, 0);
  robot.imu.To(90);
  robot.mech.ToX(2);
  intake.spinFor(directionType::fwd, .3, rev, 100, velocityUnits::pct, true);
  robot.base.For(2, 90);
  robot.base.For(-.1, 90);
  // robot.base.driveFor(-.1, 40);
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