#pragma once
#include "..\src\calc\PID\PID.h"

class BASE_DRIVE //: public PID
{
  private:
  public:
  BASE_DRIVE();
  static PID pidTheta;
  static PID pid;
  void defaultPID();
  static void To();
  static void For();
  static void polarFor();
  void To(double target, double targetTheta);
  void For(double target, double targetTheta);
  void aTo();
  void aFor();
  void aTo(double target, double targetTheta);
  void aFor(double target, double targetTheta);
  void driveFor(double positionRev, int driveSpeed);
};