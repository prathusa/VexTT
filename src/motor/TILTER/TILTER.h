#pragma once
#include "..\src\calc\PID\PID.h"

class TILTER //: public PID
{
  private:
  public:
  TILTER();
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
  void Stack();
  void aStack();
};