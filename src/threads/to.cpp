#include "main.h"

vex::thread TO::main; 
vex::thread TO::alt;
PID TO::pid(10, 2, 0);
PID TO::pid_theta;
PID TO::pid_etc;
TO::STATUS TO::status = TO::STATUS::IDLE;
feature::Coordinate TO::pos;
double TO::accuracy = .93;


void TO::update(feature::Coordinate target)
{
  if (status == STATUS::IDLE)
  {
    if ( config::MOTORS::BASE == ROBOT::motors )
    {
      // main = move(thread(base));
    }
    // switch (ROBOT::motors)
    // {
    //   case config::MOTORS::BASE:
    //   cout << "this case";
    //   main = move(thread(base));
    //   cout << "this case";
    //   break;
    //   case config::MOTORS::H:
    //   main = move(thread(h));
    //   break;
    //   case config::MOTORS::HOLO:
    //   main = move(thread(holo));
    //   break;
    //   case config::MOTORS::MECH:
    //   main = move(thread(mech));
    //   break;
    // }
  }
    // main.interrupt();
  status = STATUS::RUNNING;
  this->pos = target;
  base();
  
  // main = move(thread());
}

void TO::base()
{
  double volts;
  double thetaVolts;
  // pid.setPID(10, 1.5, 0.05);
  pid_theta.setPID(.35, 0.0065, 0.03); // This needs to be updated when PID turn constants are changed
  int time = 0;
  int timeout = 40;
  // fps.reset();
  feature::Coordinate center = robot.fps.coordinates;
  // cout << "runnin " << endl;
  while (1) 
  {
    pid.position = (robot.fps.coordinates-center).magnitude();
    pid.target = pos.magnitude();
    // cout << "pid pos: " << pos << " " << robot.fps.coordinates-center  << " " << pid.position << endl;
    volts = pid.calc(pid.target, pid.position);
    thetaVolts = pid_theta.calc(pid_theta.target, Inertial.rotation(deg));
    double tolerance = 1-TO::accuracy;
    if(std::abs(pid.error) < 7 * abs(pid.derivative) * tolerance)
      pid.integral = 0;
    if (std::abs(pid.integral) > 3)
      pid.integral = 0;
    // if((target != 0 && position/target < 0) || (position != 0 && target/position < 0))
    // {
    //   integral = 1.5;
    // }
    cout << "err : " << pid.error << endl;
    if(std::abs(pid.error) < tolerance)// && abs(pid.derivative) < 1)
    {
      status = STATUS::COMPLETE;
      wait:
      d.stop();
      break;
      this_thread::sleep_for(20);
      // this_thread::yield();
      // break;
    }
    // else if(abs(pid.derivative) < 0.01)
    // {
    //   if(time >= timeout)
    //   {
    //     status = STATUS::STUCK;
    //     goto wait;
    //   }
    //   else
    //     time += 15;
    // }
    thetaVolts = 0;
    // if(abs(volts - thetaVolts) <= 12)
    //   volts = volts - thetaVolts;
    // else
    //   volts = volts + thetaVolts;
    cout << "volts: " << volts << endl;
    d.spin(directionType::fwd, 50, percentUnits::pct);
    // l.spin(volts + thetaVolts); 
    // r.spin(fwd, volts - thetaVolts, voltageUnits::volt);
    status = STATUS::RUNNING;
    // this_thread::sleep_for(20);
    task::sleep(20);
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

double TO::tune_eval(feature::Coordinate target)
{
  double tolerance = 1-TO::accuracy;
  int timeout = 200;
  int running_time = 0;
  double running_sum = 0;
  cout << "Testing with values" << " kP: " << pid.kP  << " kI: " << pid.kI  << " kD: " << pid.kD;
  this->update(target);
  while (abs(pid.error) > tolerance)
  {
    running_sum += abs( pid.derivative );
    if (abs(pid.derivative) < .01) running_time += 20;
    if (running_time == timeout) 
    {
      running_sum = -100 + running_sum/100;
      break;
    } 
    task::sleep(20); 
  }
  this->update(feature::Coordinate());
  asap();
  cout << " result: " << running_sum << endl;
  task::sleep(300);
  return running_sum;
}

/**
Returns true if kP was modified
**/
bool TO::tp(feature::Coordinate target)
{
  double orig = pid.kP;
  double d = .3;
  //  no change evaluation
  double res = tune_eval(target);
  pid.kP = orig + d;
  // adding evalution
  double res_plus = tune_eval(target);
  pid.kP = orig - d;
  // subtracting evalution
  double res_minus = tune_eval(target);
  double best = max(res, max(res_plus, res_minus));
  if (res_plus == best)
    pid.kP = orig + d;
  else if (res_minus == best)
    pid.kP = orig - d;
  return pid.kP == orig;
}

/**
Returns true if kI was modified
**/
bool TO::ti(feature::Coordinate target)
{
  double orig = pid.kI;
  double d = .3;
  //  no change evaluation
  double res = tune_eval(target);
  pid.kI = orig + d;
  // adding evalution
  double res_plus = tune_eval(target);
  pid.kI = orig - d;
  // subtracting evalution
  double res_minus = tune_eval(target);
  double best = max(res, max(res_plus, res_minus));
  if (res_plus == best)
    pid.kI = orig + d;
  else if (res_minus == best)
    pid.kI = orig - d;
  return pid.kI == orig;
}

/**
Returns true if kD was modified
**/
bool TO::td(feature::Coordinate target)
{
  double orig = pid.kD;
  double d = .3;
  //  no change evaluation
  double res = tune_eval(target);
  pid.kD = orig + d;
  // adding evalution
  double res_plus = tune_eval(target);
  pid.kD = orig - d;
  // subtracting evalution
  double res_minus = tune_eval(target);
  double best = max(res, max(res_plus, res_minus));
  if (res_plus == best)
    pid.kD = orig + d;
  else if (res_minus == best)
    pid.kD = orig - d;
  return pid.kD == orig;
}

void TO::tuner(feature::Coordinate target)
{
  // pid.setPID(10, 1.5, 0.05);
  bool rp, ri, rd;
  do 
  {
    rp = tp(target);
    ri = ti(target);
    rd = td(target);
  }
  while (rp || ri || rd);
}