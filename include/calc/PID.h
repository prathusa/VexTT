/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.h                                                     */
/*    Author:       Pratham Baid                                              */
/*    Created:      Fri Mar 20 2020                                           */
/*    Description:  PID Calculation Library                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Near Vanilla PID class that can easily, efficiently, and cleanly be made 
// into object in robot function classes (e.g. Drive class, Arm class, Claw class).
#pragma once

class PID
{
  private:
  double stock_kPID[3];
  public:
  PID();
  PID(double kPID[]);
  PID(double kP, double kI, double kD);
  // PID(double kP, double kI, double kD, double dt, double max, double min);
  double kP = 0;
  double kI = 0;
  double kD = 0;
  double dT = .02;
  double max = 12;
  double min = -12;
  double position = 0;
  double target = 0;
  double error = 0;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;
  double prevPosition = 0;
  double prevDeriv = 0;
  double acceleration = 0;
  double Pout = 0;
  double Iout = 0;
  double Dout = 0;
  double output = 0;
  void clear();
  void resetPID();
  void setPID(double kPID[]);
  void setPID(double kP, double kI, double kD);
  void setTarget(double iTarget);
  double calc(double target, double position);
};