#pragma once
#include "..\src\calc\PID\PID.h"

class LIFTER //: public PID
{
  private:
  public:
  LIFTER();
  static PID pid;
  void defaultPID();
  static void To();
  static void For();
  void To(double target);
  void For(double target);
  void aTo();
  void aFor();
  void aTo(double target);
  void aFor(double target);
};