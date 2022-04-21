#pragma once

#include "features.h"
#include "school.h"

class TO
{
  // static feature::Coordinate pos;
  static PID pid;
  static PID pid_theta;
  static PID pid_etc;
  static vex::thread main;
  static vex::thread alt;
  static void base();
  static void h();
  static void holo();
  static void mech();
  static double accuracy;
  public:
  static feature::Coordinate pos;
  void update(feature::Coordinate target);
  static void wait() { while (status != STATUS::COMPLETE) vex::task::sleep(20); }
  static void asap() { while (status == STATUS::RUNNING) vex::task::sleep(20); }
  void set_target_accuracy(double accuracy = .93);
  enum STATUS {IDLE, RUNNING, STUCK, COMPLETE};
  static STATUS status;
};