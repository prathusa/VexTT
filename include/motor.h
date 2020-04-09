#pragma once
#include "calc\PID.h"
#include "calc\FPS.h"
#include "calc\MAPS.h"

class PID_METHODS1
{
  public:
  static void To();
  static void For();
  void aTo();
  void aFor();
};

class PID_METHODS2
{
  public:
  void To(double target);
  void For(double target);
  void aTo(double target);
  void aFor(double target);
};

class IMU : public PID_METHODS1, public PID_METHODS2
{
  private:
  public:
  IMU();
  static PID pid;
  void defaultPID();
};

class BASE : public PID_METHODS1
{
  private:
  public:
  BASE();
  static PID pidTheta;
  static PID pid;
  void defaultPID();
  static void polarFor();
  void To(double target, double targetTheta);
  void For(double target, double targetTheta);
  void aTo(double target, double targetTheta);
  void aFor(double target, double targetTheta);
  void driveFor(double positionRev, int driveSpeed);
};

// Not complete
class MECH : public BASE 
{
  private:
  public:
  MECH();
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

class HOLO : public PID_METHODS1
{
  private:
  public:
  HOLO();
  static PID pidTheta;
  static PID pid;
  void defaultPID();
  void To(double target, double targetTheta);
  void For(double target, double targetTheta);
  void aTo(double target, double targetTheta);
  void aFor(double target, double targetTheta);
  void driveFor(double positionRev, int driveSpeed);
};

class LIFTER : public PID_METHODS1, public PID_METHODS2
{
  private:
  public:
  LIFTER();
  static PID pid;
  void defaultPID();
};

class TILTER : public PID_METHODS1, public PID_METHODS2
{
  private:
  public:
  TILTER();
  static PID pid;
  void defaultPID();
  void Stack();
  void aStack();
};

class ROBOT
{
  private:
  public:
  ROBOT();
  IMU imu = IMU();
  BASE base;
  MECH mech;
  HOLO holo;
  TILTER tilter;
  LIFTER lifter;
  FPS fps;
  MAPS map;
};