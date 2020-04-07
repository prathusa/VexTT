#pragma once
#include "..\src\calc\PID\PID.h"
#include "..\src\motor\DRIVE\BASE_DRIVE\BASE_DRIVE.h"

class MECH_DRIVE : public BASE_DRIVE //, public PID
{
  private:
  public:
  MECH_DRIVE();
  static PID pidLD;
  static PID pidRD;
  void defaultPID();
  static void ToX();
  static void ForX();
  void ToX(double target);
  void ForX(double target);
  void aToX();
  void aForX();
  void aToX(double target);
  void aForX(double target);
};