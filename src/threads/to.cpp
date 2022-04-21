#include "main.h"

vex::thread TO::main; 
vex::thread TO::alt;
PID TO::pid;
PID TO::pid_theta;
PID TO::pid_etc;
TO::STATUS TO::status = TO::STATUS::IDLE;
feature::Coordinate TO::pos;
double TO::accuracy;


void TO::update(feature::Coordinate target)
{
  if (status == STATUS::IDLE)
  {
    switch (ROBOT::motors)
    {
      case config::MOTORS::BASE:
      main = move(thread(base));
      break;
      case config::MOTORS::H:
      main = move(thread(h));
      break;
      case config::MOTORS::HOLO:
      main = move(thread(holo));
      break;
      case config::MOTORS::MECH:
      main = move(thread(mech));
      break;
    }
  }
    // main.interrupt();
  
  this->pos = target;
  
  // main = move(thread());
}

void TO::base()
{
  double volts;
  double thetaVolts;
  pid.setPID(10, 1.5, 0.05);
  pid_theta.setPID(.35, 0.0065, 0.03); // This needs to be updated when PID turn constants are changed
  int time = 0;
  int timeout = 40;
  // fps.reset();
  feature::Coordinate center = robot.fps.coordinates;
  while (1) 
  {
    pid.position = (robot.fps.coordinates-center).magnitude();
    volts = pid.calc(pid.target, pid.position);
    thetaVolts = pid_theta.calc(pid_theta.target, Inertial.rotation(deg));
    double tolerance = 1-accuracy;
    if(std::abs(pid.error) < 7 * abs(pid.derivative) * tolerance)
      pid.integral = 0;
    if (std::abs(pid.integral) > 3)
      pid.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      status = STATUS::COMPLETE;
      wait:
      d.stop();
      this_thread::sleep_for(20);
      // this_thread::yield();
      // break;
    }
    else if(abs(pid.derivative) < 0.01)
    {
      if(time >= timeout)
      {
        status = STATUS::STUCK;
        goto wait;
      }
      else
        time += 15;
    }
    if(abs(volts - thetaVolts) <= 12)
      volts = volts - thetaVolts;
    else
      volts = volts + thetaVolts;
    l.spin(fwd, volts + thetaVolts, voltageUnits::volt);
    r.spin(fwd, volts - thetaVolts, voltageUnits::volt);
    status = STATUS::RUNNING;
    this_thread::sleep_for(20);
  }
  pid.resetPID();
}

void TO::h()
{
  
}

void TO::holo()
{
    
}

void TO::mech()
{
  // TODO: Implementation
}