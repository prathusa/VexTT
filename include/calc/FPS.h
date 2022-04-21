#pragma once
#include "config.h"
#include "features.h"

class FPS
{
  private:
  vex::thread main;
  // static double pos[2];
  // static double dPos[2];
  // static double prevPos[2];
  static feature::Coordinate curr;
  static feature::Coordinate delta;
  static feature::Coordinate prev;
  static void printData();
  static void twoMotorEnc();
  static void twoParaShaftEnc();
  static void twoPerpShaftEnc();
  static void twoPerpRotSen();
  public:
  FPS();
  // static double theta;
  // static double magnitude;
  // static double coordinates[2]; // 0 is X component
  //                               // 1 is Y component
  static feature::Coordinate coordinates;
  void setUpdate(config::SENSORS SETUP_TYPE);
  void start();
  void print();
  void reset();
};



