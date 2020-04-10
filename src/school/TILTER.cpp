#include "main.h"

TILTER::TILTER(){};
PID TILTER::pid = PID(1.7, 0.09, 0);

void TILTER::To()
{
  while(1)
  {
    double volts = pid.calc(pid.target, tilt.value(pct));
    double tolerance = .03;
    if(std::abs(pid.error) < tolerance * abs(pid.derivative))
      pid.integral = 0;
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      Tilt.stop();
      this_thread::yield();
      break;
    }
    Tilt.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pid.reset();
}

void TILTER::For()
{
  double position = lift.value(pct);
  pid.target += position;
  To();
}

void TILTER::To(double iTarget)
{
  pid.target = iTarget;
  To();
}

void TILTER::For(double iTarget)
{
  pid.target = iTarget;
  For();
}

void TILTER::aTo()
{
  thread async_pid = vex::thread(To);
}

void TILTER::aTo(double iTarget)
{
  pid.target = iTarget;
  aTo();
}

void TILTER::aFor()
{
  thread async_pid = vex::thread(For);
}

void TILTER::aFor(double iTarget)
{
  pid.target = iTarget;
  aFor();
}

void TILTER::Stack()
{
  while(1)
  {
    double volts = pid.calc(pid.target, tilt.value(pct));
    double tolerance = .03;
    if(std::abs(pid.error) < tolerance * abs(pid.derivative))
      pid.integral = 0;
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      Tilt.stop();
      this_thread::yield();
      break;
    }
    if(tilt.value(pct) > (tiltStack-tiltMin)*1/3 && tilt.value(pct) < (tiltStack-tiltMin)*3/4)
    {
      intake.spin(directionType::rev, 60, pct);
    }
    Tilt.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void TILTER::aStack()
{
  robot.tilter.aTo(tiltStack);
}