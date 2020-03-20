//VEX_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "v5_vcs.h"
#include "robot-config.h"
#include "manual.h"
#include "drivefunctions.h"
#include "ACCESS_OS.h"
#include "fps.h"
#include "maps.h"
#include "tuner.h"
using namespace vex;

// guiC.cpp
void pre_auton(void);

// usercontrol.cpp
void usercontrol(void);

// controls.cpp
void controls(void);

//autonomous.cpp
void autonomous(void);

//port 3&4&10&11 ded
extern ACCESS_OS os;
// extern IMU imu;
// extern PID pid;
// extern BASE_DRIVE base;
// extern MECH_DRIVE mech;
extern ROBOT robot;