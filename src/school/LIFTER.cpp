#include "main.h"

LIFTER::LIFTER(){};
PID LIFTER::pid = PID(1.7, 0.04, 0);

void LIFTER::To()
{
  while(1)
  {
    double volts = pid.calc(pid.target, lift.value(pct));
    // double tolerance = .03;
    // if(std::abs(pid.error) < tolerance * abs(pid.derivative))
    //   pid.integral = 0;
    // if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    // {
    //   Lift.stop();
    //   this_thread::yield();
    //   break;
    // }
    Lift.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pid.reset();
}

void LIFTER::For()
{
  double position = lift.value(pct);
  pid.target += position;
  To();
}

void LIFTER::To(double iTarget)
{
  pid.target = iTarget;
  To();
}

void LIFTER::For(double iTarget)
{
  pid.target = iTarget;
  For();
}

void LIFTER::aTo()
{
  thread async_pid = vex::thread(To);
}

void LIFTER::aTo(double iTarget)
{
  pid.target = iTarget;
  aTo();
}

void LIFTER::aFor()
{
  thread async_pid = vex::thread(For);
}

void LIFTER::aFor(double iTarget)
{
  pid.target = iTarget;
  aFor();
}