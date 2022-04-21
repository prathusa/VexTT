#pragma once

#include "calc\FPS.h"
#include "calc\MAPS.h"
#include "config.h"
#include "school.h"
#include "threads\to.h"

class ROBOT
{
  private:
  public:
  static FPS fps;
  static MAPS map;
  static TO to;
  static IMU imu;
  static BASE base;
  static MECH mech;
  static HOLO holo;
  static LIFTER lifter;
  static config::SENSORS sensors;
  static config::MOTORS motors;
};