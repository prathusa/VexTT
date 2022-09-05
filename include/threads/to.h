#pragma once

#include "features.h"
#include "calc/PID.h"

class TO
{
  // static feature::Coordinate pos;
  static vex::thread main;
  static vex::thread alt;
  static void base();
  static void h();
  static void holo();
  static void mech();
  double tune_eval(feature::Coordinate target);
  bool tp(feature::Coordinate target); // tune kp
  bool ti(feature::Coordinate target); // tune ki
  bool td(feature::Coordinate target); // tune kd
  static double accuracy;
  public:
  static PID pid;
  static PID pid_theta;
  static PID pid_etc;
  static feature::Coordinate pos;
  void tuner(feature::Coordinate target);
  void update(feature::Coordinate target);
  static void wait() { while (status != STATUS::COMPLETE) vex::task::sleep(20); }
  static void asap() { while (status == STATUS::RUNNING) vex::task::sleep(20); }
  void set_target_accuracy(double accuracy = .93);
  enum STATUS {IDLE, RUNNING, STUCK, COMPLETE};
  static STATUS status;
};