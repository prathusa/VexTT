#include "main.h"

BASE::BASE(){};
PID BASE::pid = PID(13, 1.5, .04);
PID BASE::pidTheta = PID();

void BASE::To() 
{
  double thetaVolts = 0;
  double volts;
  int time = 0;
  int timeout = 40;
  while (1) 
  {
    pid.position = d.position(rotationUnits::rev);
    volts = pid.calc(pid.target, pid.position);
    thetaVolts = pidTheta.calc(pidTheta.target, Inertial.rotation(deg));
    double tolerance = .005;
    if(std::abs(pid.error) < 7 * abs(pid.derivative) * tolerance)
      pid.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    if(abs(pid.derivative) < 0.01)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    if(abs(volts - thetaVolts) <= 12)
      volts = volts - thetaVolts;
    else
      volts = volts + thetaVolts;
    l.spin(fwd, volts + thetaVolts, voltageUnits::volt);
    r.spin(fwd, volts - thetaVolts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pid.resetPID();
}

void BASE::polarFor() 
{
  double thetaVolts = 0;
  pidTheta.setPID(.35, 0.0065, 0.03); // This needs to be updated when PID turn constants are changed
  double volts;
  int time = 0;
  int timeout = 40;
  // fps.reset();
  double center[] = {robot.fps.coordinates[0], robot.fps.coordinates[1]};
  while (1) 
  {
    pid.position = magn((robot.fps.coordinates[0] - center[0]), (robot.fps.coordinates[1] - center[1]));
    volts = pid.calc(pid.target, pid.position);
    thetaVolts = pidTheta.calc(pidTheta.target, Inertial.rotation(deg));
    double tolerance = .005;
    if(std::abs(pid.error) < 7 * abs(pid.derivative) * tolerance)
      pid.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pid.error) < tolerance && abs(pid.derivative) < 1)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    if(abs(pid.derivative) < 0.01)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    if(abs(volts - thetaVolts) <= 12)
      volts = volts - thetaVolts;
    else
      volts = volts + thetaVolts;
    l.spin(fwd, volts + thetaVolts, voltageUnits::volt);
    r.spin(fwd, volts - thetaVolts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pid.resetPID();
}

void BASE::For() 
{
  double position = robot.fps.coordinates[1];
  pid.target += position;
  To();
}

void BASE::To(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  To();
}

void BASE::For(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  For();
}

void BASE::aTo() 
{
  thread async_pid = vex::thread(To);
}

void BASE::aFor() 
{
  thread async_pid = vex::thread(For);
}

void BASE::aTo(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  aTo();
}

void BASE::aFor(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  aFor();
}

void BASE::driveFor(double positionRev, int driveSpeed) 
{
  double error = positionRev - d.position(rotationUnits::rev);
  double kP = driveSpeed/28.57;
  int motionless = 0;
  if (error > 0) 
  {
    while (error > 0 && motionless <= 40) 
    {
      error = positionRev - d.position(rotationUnits::rev);
      double volts = (error * kP) + 2;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=20;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(20);
    }
  }
  else if (error < 0) 
  {
    while (error < 0 && motionless <= 40) 
    {
      error = positionRev - d.position(rotationUnits::rev);
      double volts = (error * kP) - 2;
      d.spin(fwd, volts, voltageUnits::volt);
      if(dt.velocity(percentUnits::pct) == 0)
        motionless+=20;
      if(dt.velocity(percentUnits::pct) != 0)
        motionless+=0;
      vex::task::sleep(20);
    }
  }
  intake.stop();
}
