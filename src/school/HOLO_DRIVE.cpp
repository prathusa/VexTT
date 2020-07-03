#include "main.h"

HOLO::HOLO(){};
PID HOLO::pidX = PID(28, 0.0, .009); // Random numbers right now, need to be tuned 20 P is good
PID HOLO::pidY = PID(28, 0.0, .009); // Random numbers right now, need to be tuned

void HOLO::spinX(double x, voltageUnits units)
{
  ld.spin(fwd, x, units);
  rd.spin(fwd, -x, units);
}

void HOLO::spinY(double y, voltageUnits units)
{
  d.spin(fwd, y, units);
}

void HOLO::To() // Possibly can add another parameter that asks for turning degree more implementation details below
{
  double voltsX;
  double voltsY;
  int time = 0;
  int timeout = 80;
  // fps.reset();
  double center[] = {robot.fps.coordinates[0], robot.fps.coordinates[1]};
  while (1) 
  {
    pidX.position = robot.fps.coordinates[0] - center[0];
    pidY.position = robot.fps.coordinates[1] - center[1];
    voltsX = pidX.calc(pidX.target, pidX.position);
    voltsY = pidY.calc(pidY.target, pidY.position);
    double tolerance = .005;
    // if(std::abs(pidX.error) < 7 * abs(pidX.derivative) * tolerance)
    //   pidX.integral = 0;
    // if(std::abs(pidY.error) < 7 * abs(pidY.derivative) * tolerance)
    //   pidY.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    // if(std::abs(pidX.error) < tolerance && abs(pidX.derivative) < 1 && std::abs(pidY.error) < tolerance && abs(pidY.derivative) < 1)
    // {
    //   goto kill;
    // }
    if(abs(pidX.derivative) < 0.001 && abs(pidY.derivative) < 0.001)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    if(false)
    {
      kill:
      // cout << "completed" << endl;
      d.stop();
      this_thread::yield();
      break;
    }
    LeftFrontMotor.spin(fwd, sin(atan2(voltsY, voltsX) + M_PI_4)*magn(voltsX, voltsY), voltageUnits::volt); // After turning calculations, the motor turning volts calculated can be added/subtracted in the parameter of these spin functions.
    LeftRearMotor.spin(fwd, sin(atan2(voltsY, voltsX) - M_PI_4)*magn(voltsX, voltsY), voltageUnits::volt);
    RightFrontMotor.spin(fwd, sin(atan2(voltsY, voltsX) - M_PI_4)*magn(voltsX, voltsY), voltageUnits::volt);
    RightRearMotor.spin(fwd, sin(atan2(voltsY, voltsX) + M_PI_4)*magn(voltsX, voltsY), voltageUnits::volt);
    this_thread::sleep_for(20);
  }
  pidX.resetPID();
  pidY.resetPID();
}

void HOLO::For() 
{
  pidX.target += robot.fps.coordinates[0];
  pidY.target += robot.fps.coordinates[1];
  To();
}

void HOLO::To(double x, double y) 
{
  pidX.target = x;
  pidY.target = y;
  To();
}

void HOLO::For(double x, double y) 
{
  pidX.target = x;
  pidY.target = y;
  For();
}

void HOLO::aTo() 
{
  thread async_pid = vex::thread(To);
}

void HOLO::aFor() 
{
  thread async_pid = vex::thread(For);
}

void HOLO::aTo(double x, double y) 
{
  pidX.target = x;
  pidY.target = y;
  aTo();
}

void HOLO::aFor(double x, double y) 
{
  pidX.target = x;
  pidY.target = y;
  aFor();
}

void HOLO::To(double target[])
{
  To(target[0], target[1]);
}

void HOLO::For(double target[])
{
  For(target[0], target[1]);
}

void HOLO::aTo(double target[])
{
  aTo(target[0], target[1]);
}

void HOLO::aFor(double target[])
{
  aFor(target[0], target[1]);
}

void HOLO::driveFor(double x, double y, int speed)
{
  
}

void HOLO::driveFor(double target[], int speed)
{
  
}