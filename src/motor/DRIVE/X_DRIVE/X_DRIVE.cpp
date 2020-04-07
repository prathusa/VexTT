#include "main.h"

X_DRIVE::X_DRIVE(){};

PID X_DRIVE::pid = PID(13, 1.5, .04);
PID X_DRIVE::pidTheta = PID();

void X_DRIVE::To() 
{
  double thetaVolts = 0;
  // pidTheta.setPID(.35, 0.0065, 0.03); // This needs to be updated when PID turn constants are changed
  double volts;
  int time = 0;
  int timeout = 40;
  while (1) 
  {
    pid.position = robot.fps.magnitude;
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
  pid.reset();
}

void X_DRIVE::For() 
{
  double position = robot.fps.coordinates[1];
  pid.target += position;
  To();
}

void X_DRIVE::To(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  To();
}

void X_DRIVE::For(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  For();
}

void X_DRIVE::aTo() 
{
  thread async_pid = vex::thread(To);
}

void X_DRIVE::aFor() 
{
  thread async_pid = vex::thread(For);
}

void X_DRIVE::aTo(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  aTo();
}

void X_DRIVE::aFor(double iTarget, double iThetaTarget) 
{
  pidTheta.target = iThetaTarget;
  pid.target = iTarget;
  aFor();
}