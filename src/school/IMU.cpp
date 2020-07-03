#include "main.h"

IMU::IMU(){};
PID IMU::pid = PID(0.32, 0.16, 0.0105);

void IMU::To() 
{
  while (1) 
  {
    double volts = pid.calc(pid.target, Inertial.rotation());
    double angleTolerance = 1;
    if(std::abs(pid.error) < angleTolerance * abs(pid.derivative) * .09)
      pid.integral = 0;
    if(abs(pid.derivative) < 1 && std::abs(pid.error) < angleTolerance * 3) 
      goto kill;
    // volts = calc();
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < angleTolerance && abs(pid.derivative) < 10)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    l.spin(fwd, volts, voltageUnits::volt);
    r.spin(fwd, -volts, voltageUnits::volt);
    this_thread::sleep_for(30);
  }
  pid.resetPID();
}

void IMU::For() 
{
  pid.position = Inertial.rotation(deg);
  pid.target += pid.position;
  To();
}

void IMU::To(double iTarget)
{
  if(os.getValues(COLOR) == RED)
    pid.target = iTarget;
  else
    pid.target = -iTarget;
  To();
}

void IMU::For(double iTarget) 
{
  if(os.getValues(COLOR) == RED)
    pid.target = iTarget;
  else
    pid.target = -iTarget;
  For();
}

void IMU::aTo() { thread async_pid = vex::thread(To); }

void IMU::aFor() { thread async_pid = vex::thread(For); }

void IMU::aTo(double iTarget) 
{
  if(os.getValues(COLOR) == RED)
    pid.target = iTarget;
  else
    pid.target = -iTarget;
  aTo();
}

void IMU::aFor(double iTarget) 
{
  if(os.getValues(COLOR) == RED)
    pid.target = iTarget;
  else
    pid.target = -iTarget;
  aFor();
}