#pragma once

class Slew
{
  private:
  public:
  Slew();
  Slew(double accel_step, double deccel_step);
  double accel_step = 0;
  double deccel_step = 0;
  double slew(double target, double motorVelocity);
};

double magn(double i, double j);