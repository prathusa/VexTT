#pragma once
#include "..\src\motor\DRIVE\IMU\IMU.h"
#include "..\src\motor\DRIVE\BASE_DRIVE\BASE_DRIVE.h"
#include "..\src\motor\DRIVE\MECH_DRIVE\MECH_DRIVE.h"
#include "..\src\motor\TILTER\TILTER.h"
#include "..\src\motor\LIFTER\LIFTER.h"
#include "..\src\calc\FPS\FPS.h"
#include "..\src\calc\MAPS\MAPS.h"

class ROBOT
{
  private:
  public:
  ROBOT();
  IMU imu = IMU();
  BASE_DRIVE base = BASE_DRIVE();
  MECH_DRIVE mech = MECH_DRIVE();
  TILTER tilter = TILTER();
  LIFTER lifter = LIFTER();
  FPS fps = FPS();
  MAPS map = MAPS();
};

ROBOT::ROBOT(){};