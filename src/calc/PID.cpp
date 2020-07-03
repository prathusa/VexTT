/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.cpp                                                   */
/*    Author:       Pratham Baid                                              */
/*    Created:      Fri Mar 20 2020                                           */
/*    Description:  PID Calculation Library                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "main.h"

PID::PID()
{
  this->kP = stock_kPID[0] = 0;
  this->kI = stock_kPID[1] = 0;
  this->kD = stock_kPID[2] = 0;
};
PID::PID(double kP, double kI, double kD)
{
  this->kP = stock_kPID[0] = kP;
  this->kI = stock_kPID[1] = kI;
  this->kD = stock_kPID[2] = kD;
};
PID::PID(double kPID[])
{
  this->kP = stock_kPID[0] = kPID[0];
  this->kI = stock_kPID[1] = kPID[1];
  this->kD = stock_kPID[2] = kPID[2];
};

void PID::setTarget(double iTarget) { target = iTarget; }

void PID::setPID(double kP, double kI, double kD)
{
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
}

void PID::setPID(double kPID[])
{
  this->kP = kPID[0];
  this->kI = kPID[1];
  this->kD = kPID[2];
};

double PID::calc(double target, double position) 
{
  this->target = target;
  this->position = position;

  error = target - position;
  // Proportional term
  Pout = kP * error;

  // Integral term
  integral += error * dT;
  Iout = kI * integral;

  // Derivative term
  derivative = (error - prevError)/dT;
  // if(std::abs(derivative) > std::abs(acceleration + prevDeriv) && prevDeriv != 0) // Optional to smooth Derivative calculations and prevent derivative kick
  //   derivative = acceleration + prevDeriv; // Acceleration is added to previous derivative to predict the current derivative and then compare it to the calculated derivative
  Dout = kD * derivative;

  // Calculate total output
  output = Pout + Iout + Dout;

  // Restrict to max/min
  if (output > max)
    output = max;
  else if (output < min)
    output = min;

  double integralCap = 3.5;

  if (Iout > integralCap)
    Iout = integralCap;
  else if (Iout < -integralCap)
    Iout = -integralCap;
  // if (std::abs(error) < tolerance) // Optional, if your PID doesn't stop and blows past the target, this prevents Integral windup, 
  // {                                // highly recommended for PIDs that don't fight gravity (e.g. drive train PID, PID on your base).
  //   integral = 0;                  // However, this should most likely be implemented in the movement control function rather than in this general use class
  //   output = 0;                    // since it can interefere with other PID objects where you do want the PID windup 
  // }                                // like in situations where a motor is fighting gravity, (e.g. Lift)

  // Save error to previous error
  acceleration = derivative - prevDeriv;
  prevDeriv = derivative;
  prevPosition = position;
  prevError = error;

  return output;
}

void PID::resetPID()
{
  kP = stock_kPID[0];
  kI = stock_kPID[1];
  kD = stock_kPID[2];
}

void PID::clear()
{
  dT = .02;
  max = 12;
  min = -12;
  position = 0;
  target = 0;
  error = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
  prevPosition = 0;
  prevDeriv = 0;
  acceleration = 0;
  Pout = 0;
  Iout = 0;
  Dout = 0;
  output = 0;
}

// -----------------------------PID Code template:
/*
Instructions:
Create a PID object in a class that you want PID in

For example:
class DEMO {
  public:
  DEMO();
  PID pid = PID(0, 0, 0);
};

And then create functions in that class that use the calculations from the PID object in that class
Example functions are below but an empty parameter function is required for threading 
(aka, async, which allows for functions to run in tandom, the same as putting a false bool in waitForCompletion parameter of a regular function)

Anything that you want to be threadable needs to be static to be made into a thread. 
You can declare a function static in the class definition and requires no additional changes to the actual function.

void PID::To()
{
  double errTolerance = 0.05; 
  while(1)
  {
    double volts = calc(pid.target, motor.getPosition());
    if(abs(pid.error) < errTolerance) // Checks if error is in tolerance range (range: tolerance +- target)
    {
      motor.stop();
      this_thread::yield();
      break;
    }
    m.spin(fwd, volts, voltageUnits::volt);
    this_thread::sleep_for(20);
  }
}

void PID::For()
{
  position = m.position(rev);
  target += position;
  To();
}

void PID::To(double target)
{
  pid.target = target;
  To();
}

void PID::For(double target)
{
  pid.target = target;
  For();
}

void PID::aTo()
{
  thread async_pid = vex::thread(To);
}

void PID::aFor()
{
  thread async_pid = vex::thread(For);
}

void PID::aTo(double target)
{
  pid.target = target;
  aTo();
}

void PID::aFor(double target)
{
  pid.target = target;
  aFor();
}

If all of the functions are added in the DEMO class then it should look something like this:

// file: Demo.h
class DEMO {
  public:
  DEMO();
  static PID pid = PID(0, 0, 0);
  static void To();
  static void For();
  static void To(double target);
  static void For(double target);
  void aTo(double target);
  void aFor(double target);
};

// file: Demo.cpp

*/