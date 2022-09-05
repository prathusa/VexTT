#pragma once

#include "calc\FPS.h"
#include "config.h"
#include "threads\to.h"

class ROBOT
{
  private:
  public:
  static FPS fps;
  static TO to;
  static config::SENSORS sensors;
  static config::MOTORS motors;
};