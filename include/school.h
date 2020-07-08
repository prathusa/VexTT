#pragma once
// It's called school because it holds a bunch of classes. Get it?
#include "calc\PID.h"
#include "calc\FPS.h"
#include "calc\MAPS.h"

class IMU
{
  private:
  public:
  IMU();
  static PID pid;
  static void To();
  static void For();
  void aTo();
  void aFor();
  void To(double target);
  void For(double target);
  void aTo(double target);
  void aFor(double target);
};

class BASE
{
  private:
  public:
  BASE();
  static PID pidTheta;
  static PID pid;
  static void To();
  static void For();
  void aTo();
  void aFor();
  void To(double target, double targetTheta);
  void For(double target, double targetTheta);
  void aTo(double target, double targetTheta);
  void aFor(double target, double targetTheta);
  static void polarFor();
  void driveFor(double revolutions, int speed);
  void driveTo(double revolutions, int speed);
};

// Not complete
class MECH
{
  private:
  public:
  MECH();
  static PID pidLD;
  static PID pidRD;
  static void ToX();
  static void ForX();
  void ToX(double target);
  void ForX(double target);
  void aToX();
  void aForX();
  void aToX(double target);
  void aForX(double target);
};

class HOLO
{
  private:
  static void spinX(double x, vex::voltageUnits units);
  static void spinY(double y, vex::voltageUnits units);
  public:
  HOLO();
  static PID pidLF;
  static PID pidLR;
  static PID pidRF;
  static PID pidRR;
  static double toLFRR(double x, double y);
  static double toLRRF(double x, double y);
  static void setTarget(double x, double y);
  static void To();
  static void For();
  void aTo();
  void aFor();
  void To(double x, double y);
  void For(double x, double y);
  void aTo(double x, double y);
  void aFor(double x, double y);
  void To(double target[]);
  void For(double target[]);
  void aTo(double target[]);
  void aFor(double target[]);
  void driveFor(double x, double y, int speed);
  void driveFor(double target[], int speed);
};

class HDRIVE 
{
  private:
  public:
  HDRIVE();
  static PID pidX;
  static PID pidY;
  static void To();
  static void For();
  void aTo();
  void aFor();
  void To(double magnitude);
  void For(double magnitude);
  void aTo(double magnitude);
  void aFor(double magnitude);
  void To(double x, double y);
  void For(double x, double y);
  void aTo(double x, double y);
  void aFor(double x, double y);
  void To(double position[]);
  void For(double distance[]);
  void aTo(double position[]);
  void aFor(double distance[]);
};

class LIFTER
{
  private:
  public:
  LIFTER();
  static PID pid;
  static void To();
  static void For();
  void aTo();
  void aFor();
  void To(double target);
  void For(double target);
  void aTo(double target);
  void aFor(double target);
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
  LIFTER lifter;
  FPS fps;
  MAPS map;
};