#pragma once
#include "..\src\calc\PID\PID.h"

class X_DRIVE
{
  private:
  public:
  X_DRIVE();
  static PID pidTheta;
  static PID pid;
  void defaultPID();
  static void To();
  static void For();
  void To(double target, double targetTheta);
  void For(double target, double targetTheta);
  void aTo();
  void aFor();
  void aTo(double target, double targetTheta);
  void aFor(double target, double targetTheta);
  void driveFor(double positionRev, int driveSpeed);
};