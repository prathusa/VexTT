#include "main.h"
using namespace std;

//PID Presets

double magn(double i, double j)
{
  return sqrt(pow(i, 2) + pow(j, 2));
}

//slew control
int accel_step = 12;
int deccel_step = 12; // Probabily needs to be reduced 

int slew(int target, double iMotor)
{
  int step;
  int returnSpeed;

  if(std::abs(iMotor) < abs(target))
    step = accel_step;
  else
    step = deccel_step;

  if(target > iMotor + step)
    returnSpeed = iMotor + step;
  else if(target < iMotor - step)
    returnSpeed = iMotor - step;
  else
    returnSpeed = target;

  return returnSpeed;
}

double calc_turn_angle(double angle)
{
  return baseDiagonal * angle * M_PI / 360;
}



// double BASE_DRIVE::thetaVolts = 0;