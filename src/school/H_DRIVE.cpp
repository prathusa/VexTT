#include "main.h"

HDRIVE::HDRIVE(){};
PID HDRIVE::pidX = PID(13, 1.5, .04);
PID HDRIVE::pidY = PID(13, 1.5, .04);

void HDRIVE::To() 
{
  double voltsX;
  double voltsY;
  int time = 0;
  int timeout = 40;
  // fps.reset();
  double center[] = {robot.fps.coordinates.x(), robot.fps.coordinates.y()};
  while (1) 
  {
    pidX.position = robot.fps.coordinates.x() - center[0];
    pidY.position = robot.fps.coordinates.y() - center[1];
    voltsX = pidX.calc(pidX.target, pidX.position);
    voltsY = pidY.calc(pidY.target, pidY.position);
    double tolerance = .005;
    if(std::abs(pidX.error) < 7 * abs(pidX.derivative) * tolerance)
      pidX.integral = 0;
    if(std::abs(pidY.error) < 7 * abs(pidY.derivative) * tolerance)
      pidY.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    if(std::abs(pidX.error) < tolerance && abs(pidX.derivative) < 1 && std::abs(pidY.error) < tolerance && abs(pidY.derivative) < 1)
    {
      kill:
      d.stop();
      this_thread::yield();
      break;
    }
    if(abs(pidX.derivative) < 0.01 && abs(pidY.derivative) < 0.01)
    {
      if(time >= timeout)
        goto kill;
      else
        time += 20;
    }
    // x.spin(fwd, voltsX, voltageUnits::volt); // need to tell strafe wheel to spin
    // y.spin(fwd, voltsY, voltageUnits::volt); // need to tell all forward facing wheels to spin
    this_thread::sleep_for(20);
  }
  pidX.resetPID();
  pidY.resetPID();
}