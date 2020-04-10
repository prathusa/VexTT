#include "main.h"

MECH::MECH(){};
PID MECH::pidLD = PID(10, 1.5, .05);
PID MECH::pidRD = PID(10, 1.5, .05);

void MECH::ToX() 
{
  int timeLD = 0;
  int timeRD = 0;
  int timeoutLD = 60;
  int timeoutRD = 60;
  bool isDeadLD = false;
  bool isDeadRD = false;
  while (1) 
  {
    double voltsLD = pidLD.calc(pidLD.target, ld.position(rev));
    double voltsRD = pidRD.calc(pidRD.target, rd.position(rev));
    double tolerance = .03;
    if(std::abs(pidLD.error) < tolerance * abs(pidLD.derivative))
      pidLD.integral = 0;
    if(std::abs(pidRD.error) < tolerance * abs(pidRD.derivative))
      pidRD.integral = 0;
    if(std::abs(pidLD.error) < tolerance && abs(pidLD.derivative) < 1)
    {
      killLD:
      isDeadLD = true;
      ld.stop();
    }
    if(std::abs(pidRD.error) < tolerance && abs(pidRD.derivative) < 1)
    {
      killRD:
      isDeadRD = true;
      rd.stop();
    }
    if(abs(pidLD.derivative) < 0.01)
    {
      if(timeLD >= timeoutLD)
        goto killLD;
      else
        timeLD += 20;
    }
    if(abs(pidRD.derivative) < 0.01)
    {
      if(timeRD >= timeoutRD)
        goto killRD;
      else
        timeRD += 20;
    }
    ld.spin(fwd, voltsLD, volt);
    rd.spin(fwd, voltsRD, volt);
    this_thread::sleep_for(20);
  }
  pid.reset();
}

void MECH::ForX() 
{
  pidLD.target += pidLD.position;
  pidRD.target += pidRD.position;
  ToX();
}

void MECH::ToX(double iTarget) 
{
  if(os.getValues(COLOR) == BLUE)
    iTarget = -iTarget;
  pidLD.target = iTarget;
  pidRD.target = -iTarget;
  ToX();
}

void MECH::ForX(double iTarget) 
{
  if(os.getValues(COLOR) == BLUE)
    iTarget = -iTarget;
  pidLD.target = iTarget;
  pidRD.target = -iTarget;
  ForX();
}

void MECH::aToX() 
{
  thread async_pid = vex::thread(ToX);
}

void MECH::aForX() 
{
  thread async_pid = vex::thread(ForX);
}

void MECH::aToX(double iTarget) 
{
  if(os.getValues(COLOR) == BLUE)
    iTarget = -iTarget;
  pidLD.target = iTarget;
  pidRD.target = -iTarget;
  aToX();
}

void MECH::aForX(double iTarget) 
{
  if(os.getValues(COLOR) == BLUE)
    iTarget = -iTarget;
  pidLD.target = iTarget;
  pidRD.target = -iTarget;
  aForX();
}