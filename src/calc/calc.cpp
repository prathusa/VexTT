#include "main.h"
using namespace std;

//PID Presets

//slew control

calc::Slew::Slew()
{
  accel_step = 0;
  deccel_step = 0;
}

calc::Slew::Slew(double accel_step, double deccel_step)
{
  this->accel_step = accel_step;
  this->deccel_step = deccel_step;
}

double calc::Slew::slew(double target, double motorVelocity)
{
  double step;
  double returnSpeed;

  if(std::abs(motorVelocity) < abs(target))
    step = accel_step;
  else
    step = deccel_step;

  if(target > motorVelocity + step)
    returnSpeed = motorVelocity + step;
  else if(target < motorVelocity - step)
    returnSpeed = motorVelocity - step;
  else
    returnSpeed = target;

  return returnSpeed;
}

double calc_turn_angle(double angle)
{
  return baseDiagonal * angle * M_PI / 360;
}



// double BASE_DRIVE::thetaVolts = 0;